/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniRT <miniRT@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:00:00 by miniRT           #+#    #+#             */
/*   Updated: 2025/11/03 00:00:00 by miniRT          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec3.h"
#include <math.h>

/*
 * create_camera_basis - 카메라의 로컬 좌표계 생성
 * @orientation: 카메라가 바라보는 방향 벡터
 * @right: 카메라의 오른쪽 방향 벡터 (출력)
 * @up: 카메라의 위쪽 방향 벡터 (출력)
 * @forward: 카메라의 정면 방향 벡터 (출력)
 *
 * 카메라의 방향(orientation)으로부터 세 개의 직교하는 단위 벡터를 생성합니다.
 * 이 벡터들은 카메라만의 로컬 좌표계를 형성합니다.
 *
 * 동작 과정:
 * 1. forward: 카메라가 바라보는 방향 (정규화된 orientation)
 * 2. world_up: 세계 좌표계의 위 방향
 *    - forward가 거의 수직(y > 0.999)이면 x축 사용
 *    - 그 외에는 y축(0,1,0) 사용
 * 3. right: world_up과 forward의 외적으로 계산 (카메라의 오른쪽)
 * 4. up: forward와 right의 외적으로 계산 (카메라의 위쪽)
 *
 * 외적의 순서가 중요합니다: 오른손 좌표계를 유지하기 위해
 * right = world_up × forward
 * up = forward × right
 */
static void	create_camera_basis(t_vec3 orientation, t_vec3 *right,
	t_vec3 *up, t_vec3 *forward)
{
	t_vec3	world_up;

	*forward = vec3_normalize(orientation);
	if (fabs(forward->y) > 0.999)
		world_up = vec3_new(1, 0, 0);
	else
		world_up = vec3_new(0, 1, 0);
	*right = vec3_normalize(vec3_cross(world_up, *forward));
	*up = vec3_normalize(vec3_cross(*forward, *right));
}

/*
 * calculate_ray_direction - 특정 픽셀로 향하는 광선의 방향 계산
 * @camera: 카메라 정보 (위치, 방향, FOV)
 * @i: 픽셀의 x 좌표
 * @j: 픽셀의 y 좌표
 * @wh: 화면 크기 배열 [width, height]
 *
 * 레이트레이싱의 핵심: 각 픽셀마다 카메라에서 출발하는 광선을 생성합니다.
 *
 * 동작 과정:
 * 1. FOV를 라디안으로 변환
 * 2. 화면 비율(aspect ratio) 계산
 * 3. 픽셀 좌표를 카메라 공간의 NDC(Normalized Device Coordinates)로 변환
 *    - x_cam, y_cam은 -1 ~ 1 범위로 정규화
 *    - (i+0.5, j+0.5)는 픽셀 중앙을 샘플링 (안티앨리어싱 기본)
 *    - tan(fov/2)로 시야각에 따른 스케일 조정
 *    - y_cam의 1-2*...는 화면 좌표와 카메라 좌표의 y축 반전 처리
 * 4. 카메라 로컬 좌표계 생성 (right, up, forward)
 * 5. 최종 광선 방향 = forward + x_cam*right + y_cam*up
 *    - 가상 스크린의 해당 픽셀 위치를 관통하는 방향
 * 6. 정규화하여 단위 벡터로 변환
 *
 * 핀홀 카메라 모델(Pinhole Camera Model)을 구현합니다.
 *
 * Return: 정규화된 광선 방향 벡터
 */
static t_vec3	calculate_ray_direction(t_camera camera, int i, int j, int *wh)
{
	double	fov_rad;
	double	aspect_ratio;
	double	x_cam;
	double	y_cam;
	t_vec3	right;
	t_vec3	up;
	t_vec3	forward;
	t_vec3	dir;

	fov_rad = camera.fov * M_PI / 180.0;
	aspect_ratio = (double)wh[0] / (double)wh[1];
	x_cam = (2 * (i + 0.5) / (double)wh[0] - 1) * tan(fov_rad / 2);
	x_cam *= aspect_ratio;
	y_cam = (1 - 2 * (j + 0.5) / (double)wh[1]) * tan(fov_rad / 2);
	create_camera_basis(camera.orientation, &right, &up, &forward);
	dir = vec3_add(vec3_add(vec3_mul(right, x_cam), vec3_mul(up, y_cam)),
			forward);
	dir = vec3_normalize(dir);
	return (dir);
}

/*
 * get_ray - 특정 픽셀에 대한 광선(ray) 생성
 * @camera: 카메라 정보
 * @i: 픽셀의 x 좌표
 * @j: 픽셀의 y 좌표
 * @w: 화면 너비
 *
 * 레이트레이싱에서 사용할 광선을 생성합니다.
 * 광선은 시작점(origin)과 방향(direction)으로 정의됩니다.
 *
 * 광선의 방정식: P(t) = origin + t * direction
 * - t > 0일 때만 유효 (카메라 앞쪽)
 * - t는 광선을 따라 이동한 거리
 *
 * Return: 초기화된 광선 구조체 (origin, direction)
 */
t_ray	get_ray(t_camera camera, int i, int j, int w)
{
	t_ray	ray;
	int		wh[2];

	wh[0] = w;
	wh[1] = HEIGHT;
	ray.origin = camera.position;
	ray.direction = calculate_ray_direction(camera, i, j, wh);
	return (ray);
}
