/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniRT <miniRT@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:00:00 by miniRT           #+#    #+#             */
/*   Updated: 2025/11/03 00:00:00 by miniRT          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec3.h"

/*
 * find_closest_intersection - 광선과 가장 가까운 물체의 교점 찾기
 * @scene: 장면 정보 (물체 목록)
 * @ray: 검사할 광선
 *
 * 장면의 모든 물체에 대해 광선과의 교점을 계산하고,
 * 카메라에 가장 가까운 교점을 찾습니다.
 *
 * 동작 과정:
 * 1. 모든 물체를 순회
 * 2. 물체 타입에 따라 적절한 교점 계산 함수 호출
 *    - 구(Sphere): intersect_sphere
 *    - 평면(Plane): intersect_plane
 *    - 원기둥(Cylinder): intersect_cylinder
 * 3. t > 0 (카메라 앞쪽)이고 현재까지의 최소값보다 작으면 갱신
 * 4. 가장 가까운 교점 정보 반환
 *
 * Return: 교점 정보 (t, object), 교점 없으면 t = -1
 */
t_hit	find_closest_intersection(t_scene *scene, t_ray ray)
{
	t_hit		closest;
	t_object	*obj;
	double		t;

	closest.t = -1;
	closest.object = NULL;
	obj = scene->objects;
	while (obj)
	{
		if (obj->type == OBJ_SPHERE)
			t = intersect_sphere(ray, (t_sphere *)obj->object);
		else if (obj->type == OBJ_PLANE)
			t = intersect_plane(ray, (t_plane *)obj->object);
		else if (obj->type == OBJ_CYLINDER)
			t = intersect_cylinder(ray, (t_cylinder *)obj->object);
		else
			t = -1;
		if (t > 0 && (closest.t < 0 || t < closest.t))
		{
			closest.t = t;
			closest.object = obj;
		}
		obj = obj->next;
	}
	return (closest);
}

/*
 * calculate_normal - 교점에서의 법선 벡터 계산
 * @hit: 교점 정보 (수정됨: normal 필드가 채워짐)
 *
 * 법선 벡터는 표면에 수직인 벡터로, 조명 계산에 필수적입니다.
 * 물체 타입에 따라 계산 방법이 다릅니다:
 *
 * 1. 구(Sphere):
 *    - normal = normalize(hit_point - center)
 *    - 구의 중심에서 표면의 점으로 향하는 벡터
 *    - 항상 바깥쪽을 향함
 *
 * 2. 평면(Plane):
 *    - normal = normalize(plane.normal)
 *    - 평면의 법선은 이미 정의되어 있음
 *    - 평면의 모든 점에서 동일
 *
 * 3. 원기둥(Cylinder):
 *    - 미구현 (복잡함: 측면과 캡의 법선이 다름)
 *
 * 법선은 항상 단위 벡터(길이 1)로 정규화됩니다.
 */
static void	calculate_normal(t_hit *hit)
{
	t_sphere	*sp;
	t_plane		*pl;

	if (hit->object->type == OBJ_SPHERE)
	{
		sp = (t_sphere *)hit->object->object;
		hit->normal = vec3_normalize(vec3_sub(hit->point, sp->center));
	}
	else if (hit->object->type == OBJ_PLANE)
	{
		pl = (t_plane *)hit->object->object;
		hit->normal = vec3_normalize(pl->normal);
	}
}

/*
 * vec3_to_color - 벡터 색상(0.0~1.0)을 정수 RGB(0~255)로 변환
 * @color: 색상 벡터 (x=R, y=G, z=B, 각 0.0~1.0)
 *
 * 부동소수점 색상을 화면에 표시할 수 있는 정수 형식으로 변환합니다.
 *
 * 변환 과정:
 * 1. 각 채널을 255배 (0.0~1.0 → 0~255)
 * 2. 정수로 변환
 * 3. 범위를 벗어나면 클램핑 (0~255)
 * 4. RGB를 하나의 정수로 패킹: 0xRRGGBB
 *    - Red: 상위 16비트 (<<16)
 *    - Green: 중간 8비트 (<<8)
 *    - Blue: 하위 8비트
 *
 * 예: (1.0, 0.5, 0.0) → (255, 127, 0) → 0xFF7F00 (주황색)
 *
 * Return: 32비트 정수 RGB 색상 (0xRRGGBB)
 */
int	vec3_to_color(t_vec3 color)
{
	int	rgb[3];

	rgb[0] = (int)(color.x * 255);
	rgb[1] = (int)(color.y * 255);
	rgb[2] = (int)(color.z * 255);
	if (rgb[0] > 255)
		rgb[0] = 255;
	if (rgb[1] > 255)
		rgb[1] = 255;
	if (rgb[2] > 255)
		rgb[2] = 255;
	if (rgb[0] < 0)
		rgb[0] = 0;
	if (rgb[1] < 0)
		rgb[1] = 0;
	if (rgb[2] < 0)
		rgb[2] = 0;
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

/*
 * render_pixel - 단일 픽셀의 색상 계산 및 렌더링
 * @scene: 장면 정보
 * @data: MLX 이미지 데이터
 * @ij: 픽셀 좌표 배열 [x, y]
 *
 * 레이트레이싱의 핵심 프로세스:
 *
 * 1. 광선 생성 (get_ray)
 *    - 카메라에서 현재 픽셀로 향하는 광선 생성
 *
 * 2. 교점 찾기 (find_closest_intersection)
 *    - 광선과 장면의 모든 물체와의 교점 계산
 *    - 가장 가까운 교점 선택
 *
 * 3. 교점이 있으면:
 *    a. 교점 위치 계산: origin + t * direction
 *    b. 법선 벡터 계산 (calculate_normal)
 *    c. 조명 계산 (calculate_lighting)
 *       - 환경광, 확산광, 그림자 등
 *    d. 색상을 정수로 변환하여 이미지 버퍼에 저장
 *
 * 4. 교점이 없으면:
 *    - 검은색(0) 배경 설정
 *
 * 이미지 버퍼 인덱스: y * WIDTH + x (1차원 배열)
 */
static void	render_pixel(t_scene *scene, t_mlx_data *data, int *ij)
{
	t_ray	ray;
	t_hit	hit;
	t_vec3	color;

	ray = get_ray(scene->camera, ij[0], ij[1], WIDTH);
	hit = find_closest_intersection(scene, ray);
	if (hit.object)
	{
		hit.point = vec3_add(ray.origin, vec3_mul(ray.direction, hit.t));
		calculate_normal(&hit);
		color = calculate_lighting(scene, hit);
		data->img_data[ij[1] * WIDTH + ij[0]] = vec3_to_color(color);
	}
	else
		data->img_data[ij[1] * WIDTH + ij[0]] = 0;
}

/*
 * render_scene - 전체 장면 렌더링
 * @scene: 렌더링할 장면
 * @data: 렌더링 결과를 저장할 MLX 이미지 데이터
 *
 * 화면의 모든 픽셀에 대해 레이트레이싱을 수행합니다.
 *
 * 동작 과정:
 * 1. 화면을 위에서 아래로 (j: 0 → HEIGHT-1)
 * 2. 각 행을 왼쪽에서 오른쪽으로 (i: 0 → WIDTH-1) 순회
 * 3. 각 픽셀마다 render_pixel 호출
 *    - 광선 생성
 *    - 교점 계산
 *    - 조명 계산
 *    - 색상 저장
 *
 * 이중 루프 구조:
 * - 외부 루프: 행(j, y 좌표)
 * - 내부 루프: 열(i, x 좌표)
 *
 * 최적화 가능성:
 * - 멀티스레딩: 여러 픽셀을 병렬로 처리
 * - 타일 기반 렌더링: 화면을 작은 영역으로 나눠서 처리
 * - 적응형 샘플링: 복잡한 영역은 더 많이 샘플링
 */
void	render_scene(t_scene *scene, t_mlx_data *data)
{
	int	ij[2];

	ij[1] = 0;
	while (ij[1] < HEIGHT)
	{
		ij[0] = 0;
		while (ij[0] < WIDTH)
		{
			render_pixel(scene, data, ij);
			ij[0]++;
		}
		ij[1]++;
	}
}
