/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:04:32 by yoshin            #+#    #+#             */
/*   Updated: 2025/11/03 21:04:32 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec3.h"
#include <math.h>

/*
 * intersect_plane - 광선과 평면의 교점 계산
 * @ray: 검사할 광선 (origin, direction)
 * @plane: 평면 객체 (point, normal)
 *
 * 평면은 한 점(point)과 법선 벡터(normal)로 정의됩니다.
 * 평면의 방정식: (P - point) · normal = 0
 * (P는 평면 위의 임의의 점)
 *
 * 광선 방정식 P(t) = origin + t * direction을 평면 방정식에 대입:
 * (origin + t*direction - point) · normal = 0
 * (origin - point) · normal + t * (direction · normal) = 0
 * 
 * t를 구하면:
 * t = (point - origin) · normal / (direction · normal)
 *
 * denom = direction · normal이 0에 가까우면 광선이 평면과 평행합니다.
 * t > 0이어야 카메라 앞쪽에 있는 교점입니다.
 *
 * Return: 교점까지의 거리 t (교점 없으면 -1)
 */
double	intersect_plane(t_ray ray, t_plane *plane)
{
	double	denom;
	double	t;

	denom = vec3_dot(ray.direction, plane->normal);
	if (fabs(denom) > 1e-6)
	{
		t = vec3_dot(vec3_sub(plane->point, ray.origin), plane->normal) / denom;
		if (t > 1e-6)
			return (t);
	}
	return (-1.0);
}
