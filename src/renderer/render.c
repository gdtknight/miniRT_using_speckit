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
