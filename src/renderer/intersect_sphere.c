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
