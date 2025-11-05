/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
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
 * solve_quadratic - 2차 방정식 풀이
 * @abc: 계수 배열 [a, b, c] (ax² + bx + c = 0)
 *
 * 2차 방정식의 해를 판별식(discriminant)을 이용하여 구합니다.
 * 판별식 = b² - 4ac
 *
 * 판별식에 따른 해의 개수:
 * - 음수: 실근 없음 (광선이 구와 만나지 않음)
 * - 0: 중근 (광선이 구에 접함)
 * - 양수: 서로 다른 두 실근 (광선이 구를 관통)
 *
 * 두 해(t1, t2) 중 양수이면서 더 작은 값을 반환합니다.
 * (카메라에 더 가까운 교점을 선택)
 *
 * Return: 가장 가까운 교점의 t 값, 교점 없으면 -1
 */
static double	solve_quadratic(double abc[3])
{
	double	discriminant;
	double	t1;
	double	t2;

	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0)
		return (-1.0);
	t1 = (-abc[1] - sqrt(discriminant)) / (2.0 * abc[0]);
	t2 = (-abc[1] + sqrt(discriminant)) / (2.0 * abc[0]);
	if (t1 > 0 && (t2 < 0 || t1 < t2))
		return (t1);
	if (t2 > 0)
		return (t2);
	return (-1.0);
}

/*
 * intersect_sphere - 광선과 구의 교점 계산
 * @ray: 검사할 광선 (origin, direction)
 * @sphere: 구 객체 (center, radius)
 *
 * 광선-구 교점 계산은 2차 방정식을 풀어서 수행합니다.
 *
 * 광선 방정식: P(t) = origin + t * direction
 * 구 방정식: |P - center|² = radius²
 *
 * 광선 방정식을 구 방정식에 대입하면:
 * |origin + t*direction - center|² = radius²
 * 
 * oc = origin - center라 하면:
 * |oc + t*direction|² = radius²
 * (oc + t*dir)·(oc + t*dir) = radius²
 * 
 * 전개하면 2차 방정식:
 * a*t² + b*t + c = 0
 * 여기서:
 * a = direction · direction (항상 1, direction이 정규화되어 있으므로)
 * b = 2 * (oc · direction)
 * c = oc · oc - radius²
 *
 * Return: 교점까지의 거리 t (교점 없으면 -1)
 */
double	intersect_sphere(t_ray ray, t_sphere *sphere)
{
	t_vec3	oc;
	double	abc[3];

	oc = vec3_sub(ray.origin, sphere->center);
	abc[0] = vec3_dot(ray.direction, ray.direction);
	abc[1] = 2.0 * vec3_dot(oc, ray.direction);
	abc[2] = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
	return (solve_quadratic(abc));
}
