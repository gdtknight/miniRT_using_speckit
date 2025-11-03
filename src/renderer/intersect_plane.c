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
