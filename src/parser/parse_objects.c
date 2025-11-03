/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:04:42 by yoshin            #+#    #+#             */
/*   Updated: 2025/11/03 21:04:42 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

t_vec3	parse_vec3(char *str);

static t_vec3	parse_color(char *str)
{
	t_vec3	color;
	char	**parts;

	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2])
		return ((t_vec3){0, 0, 0});
	color.x = atof(parts[0]) / 255.0;
	color.y = atof(parts[1]) / 255.0;
	color.z = atof(parts[2]) / 255.0;
	return (color);
}

void	parse_sphere(char **parts, t_scene *scene)
{
	t_object	*obj;
	t_sphere	*sp;

	sp = malloc(sizeof(t_sphere));
	obj = malloc(sizeof(t_object));
	if (!sp || !obj)
		return ;
	sp->center = parse_vec3(parts[1]);
	sp->radius = atof(parts[2]) / 2.0;
	obj->color = parse_color(parts[3]);
	obj->type = OBJ_SPHERE;
	obj->object = sp;
	obj->next = scene->objects;
	scene->objects = obj;
}

void	parse_plane(char **parts, t_scene *scene)
{
	t_object	*obj;
	t_plane		*pl;

	pl = malloc(sizeof(t_plane));
	obj = malloc(sizeof(t_object));
	if (!pl || !obj)
		return ;
	pl->point = parse_vec3(parts[1]);
	pl->normal = parse_vec3(parts[2]);
	obj->color = parse_color(parts[3]);
	obj->type = OBJ_PLANE;
	obj->object = pl;
	obj->next = scene->objects;
	scene->objects = obj;
}

void	parse_cylinder(char **parts, t_scene *scene)
{
	t_object	*obj;
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	obj = malloc(sizeof(t_object));
	if (!cy || !obj)
		return ;
	cy->center = parse_vec3(parts[1]);
	cy->axis = parse_vec3(parts[2]);
	cy->diameter = atof(parts[3]);
	cy->height = atof(parts[4]);
	obj->color = parse_color(parts[5]);
	obj->type = OBJ_CYLINDER;
	obj->object = cy;
	obj->next = scene->objects;
	scene->objects = obj;
}
