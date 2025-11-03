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

static t_vec3	calculate_ray_direction(double fov, int i, int j, int *wh)
{
	double	fov_rad;
	double	aspect_ratio;
	double	x_cam;
	double	y_cam;
	t_vec3	dir;

	fov_rad = fov * M_PI / 180.0;
	aspect_ratio = (double)wh[0] / (double)wh[1];
	x_cam = (2 * (i + 0.5) / (double)wh[0] - 1) * tan(fov_rad / 2);
	x_cam *= aspect_ratio;
	y_cam = (1 - 2 * (j + 0.5) / (double)wh[1]) * tan(fov_rad / 2);
	dir = vec3_new(x_cam, y_cam, 1);
	dir = vec3_normalize(dir);
	return (dir);
}

t_ray	get_ray(t_camera camera, int i, int j, int w)
{
	t_ray	ray;
	int		wh[2];

	wh[0] = w;
	wh[1] = HEIGHT;
	ray.origin = camera.position;
	ray.direction = calculate_ray_direction(camera.fov, i, j, wh);
	return (ray);
}
