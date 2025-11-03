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

t_vec3	calculate_lighting(t_scene *scene, t_hit hit)
{
	t_vec3	color;

	color = get_ambient_light(scene, hit.object->color);
	color = add_diffuse_light(scene, hit, color);
	color = clamp_color(color);
	return (color);
}
