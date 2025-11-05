/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:04:35 by yoshin            #+#    #+#             */
/*   Updated: 2025/11/03 21:04:35 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec3.h"

/*
 * clamp_color - 색상 값을 0.0 ~ 1.0 범위로 제한
 * @color: 제한할 색상 벡터
 *
 * 조명 계산 결과가 0~1 범위를 벗어날 수 있으므로 클램핑합니다.
 * - 1.0 초과: 1.0으로 제한 (너무 밝은 색)
 * - 0.0 미만: 0.0으로 제한 (음수 색상 방지)
 *
 * 각 RGB 채널을 독립적으로 클램핑합니다.
 *
 * Return: 0.0 ~ 1.0 범위로 제한된 색상
 */
static t_vec3	clamp_color(t_vec3 color)
{
	if (color.x > 1.0)
		color.x = 1.0;
	if (color.y > 1.0)
		color.y = 1.0;
	if (color.z > 1.0)
		color.z = 1.0;
	if (color.x < 0.0)
		color.x = 0.0;
	if (color.y < 0.0)
		color.y = 0.0;
	if (color.z < 0.0)
		color.z = 0.0;
	return (color);
}

/*
 * get_ambient_light - 환경광(Ambient Light) 계산
 * @scene: 장면 정보 (ambient_light 포함)
 * @obj_color: 물체의 기본 색상
 *
 * 환경광은 모든 방향에서 균일하게 들어오는 간접광을 시뮬레이션합니다.
 * 실제로는 다른 물체에서 반사된 빛이지만, 계산 비용을 줄이기 위해
 * 단순히 모든 물체에 일정한 밝기를 더합니다.
 *
 * 계산 공식:
 * ambient = obj_color * ambient_light_color * ambient_ratio
 *
 * - obj_color: 물체 고유의 색상
 * - ambient_light_color: 환경광의 색상
 * - ambient_ratio: 환경광의 강도 (0.0 ~ 1.0)
 *
 * 각 RGB 채널을 독립적으로 곱합니다.
 *
 * Return: 환경광 기여도
 */
static t_vec3	get_ambient_light(t_scene *scene, t_vec3 obj_color)
{
	t_vec3	ambient;

	if (scene->ambient_light)
	{
		ambient.x = obj_color.x * scene->ambient_light->color.x
			* scene->ambient_light->ratio;
		ambient.y = obj_color.y * scene->ambient_light->color.y
			* scene->ambient_light->ratio;
		ambient.z = obj_color.z * scene->ambient_light->color.z
			* scene->ambient_light->ratio;
	}
	else
	{
		ambient.x = 0;
		ambient.y = 0;
		ambient.z = 0;
	}
	return (ambient);
}

/*
 * is_in_shadow - 그림자 판정 (Shadow Ray 테스트)
 * @scene: 장면 정보 (물체 목록)
 * @point: 검사할 점의 위치
 * @light: 광원 정보
 *
 * 특정 점이 광원으로부터 그림자 안에 있는지 판단합니다.
 *
 * 동작 과정:
 * 1. 점에서 광원으로 향하는 방향 벡터 계산
 * 2. 광원까지의 거리 계산
 * 3. Shadow Ray 생성 (점에서 광원 방향으로)
 *    - origin에 0.001을 더해 자기 자신과의 교점을 방지 (shadow acne 방지)
 * 4. Shadow Ray와 장면의 모든 물체의 교점 검사
 * 5. 교점이 광원보다 가까우면 그림자 안
 *
 * Return: 1 (그림자 안), 0 (직접 조명 받음)
 */
static int	is_in_shadow(t_scene *scene, t_vec3 point, t_light *light)
{
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	t_vec3	light_dir;
	double	light_distance;

	light_dir = vec3_sub(light->position, point);
	light_distance = vec3_length(light_dir);
	shadow_ray.origin = vec3_add(point, vec3_mul(light_dir, 0.001));
	shadow_ray.direction = vec3_normalize(light_dir);
	shadow_hit = find_closest_intersection(scene, shadow_ray);
	if (shadow_hit.object && shadow_hit.t < light_distance)
		return (1);
	return (0);
}

/*
 * add_diffuse_light - 확산 반사광(Diffuse Reflection) 계산
 * @scene: 장면 정보 (광원 목록)
 * @hit: 광선과 물체의 교점 정보 (위치, 법선, 물체)
 * @color: 현재까지 누적된 색상
 *
 * Lambert의 코사인 법칙을 적용한 확산 반사를 시뮬레이션합니다.
 * 표면이 거칠어서 빛이 모든 방향으로 균일하게 반사되는 경우입니다.
 *
 * 각 광원에 대해:
 * 1. 그림자 검사 (is_in_shadow)
 * 2. 그림자가 아니면 확산광 계산
 *    - light_dir: 교점에서 광원으로의 정규화된 방향
 *    - diff = normal · light_dir (코사인 값)
 *    - diff < 0이면 0으로 클램핑 (뒷면 조명 무시)
 * 3. 확산광 = obj_color * light_color * light_ratio * diff
 *    - diff가 클수록 (법선과 광원 방향이 평행할수록) 밝아짐
 * 4. 모든 광원의 기여도를 누적
 *
 * Lambert's Cosine Law: 반사되는 빛의 양은 입사각의 코사인에 비례
 *
 * Return: 확산광이 더해진 색상
 */
static t_vec3	add_diffuse_light(t_scene *scene, t_hit hit, t_vec3 color)
{
	t_light	*light;
	t_vec3	light_dir;
	double	diff;
	t_vec3	diffuse;

	light = scene->lights;
	while (light)
	{
		if (!is_in_shadow(scene, hit.point, light))
		{
			light_dir = vec3_normalize(vec3_sub(light->position, hit.point));
			diff = vec3_dot(hit.normal, light_dir);
			if (diff < 0)
				diff = 0;
			diffuse.x = hit.object->color.x * light->color.x
				* light->ratio * diff;
			diffuse.y = hit.object->color.y * light->color.y
				* light->ratio * diff;
			diffuse.z = hit.object->color.z * light->color.z
				* light->ratio * diff;
			color = vec3_add(color, diffuse);
		}
		light = light->next;
	}
	return (color);
}

/*
 * calculate_lighting - 최종 조명 계산
 * @scene: 장면 정보 (조명, 물체)
 * @hit: 광선과 물체의 교점 정보
 *
 * Phong 조명 모델의 단순화 버전을 구현합니다.
 * 
 * 최종 색상 = 환경광 + 확산 반사광
 * 
 * 1. 환경광(Ambient): 간접광 시뮬레이션
 * 2. 확산광(Diffuse): 직접 조명, Lambert 코사인 법칙
 * 
 * 참고: 완전한 Phong 모델은 다음을 포함:
 * - Ambient (구현됨)
 * - Diffuse (구현됨)
 * - Specular (미구현): 반짝이는 하이라이트
 *
 * 계산 후 0.0 ~ 1.0 범위로 클램핑하여 오버플로우 방지
 *
 * Return: 최종 픽셀 색상 (0.0 ~ 1.0 범위)
 */
t_vec3	calculate_lighting(t_scene *scene, t_hit hit)
{
	t_vec3	color;

	color = get_ambient_light(scene, hit.object->color);
	color = add_diffuse_light(scene, hit, color);
	color = clamp_color(color);
	return (color);
}
