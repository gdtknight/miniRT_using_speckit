/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniRT <miniRT@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:00:00 by miniRT           #+#    #+#             */
/*   Updated: 2025/11/03 00:00:00 by miniRT          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

static void	free_parts(char **parts)
{
	int	i;

	if (!parts)
		return ;
	i = 0;
	while (parts[i])
	{
		free(parts[i]);
		i++;
	}
	free(parts);
}

t_vec3	parse_color(char *str)
{
	t_vec3	color;
	char	**parts;

	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2])
	{
		free_parts(parts);
		return ((t_vec3){0, 0, 0});
	}
	color.x = atof(parts[0]) / 255.0;
	color.y = atof(parts[1]) / 255.0;
	color.z = atof(parts[2]) / 255.0;
	free_parts(parts);
	return (color);
}

t_vec3	parse_vec3(char *str)
{
	t_vec3	vec;
	char	**parts;

	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2])
	{
		free_parts(parts);
		return ((t_vec3){0, 0, 0});
	}
	vec.x = atof(parts[0]);
	vec.y = atof(parts[1]);
	vec.z = atof(parts[2]);
	free_parts(parts);
	return (vec);
}

t_vec3	parse_color(char *str);

void	parse_ambient(char **parts, t_scene *scene)
{
	if (!parts || !parts[1] || !parts[2])
		return ;
	scene->ambient_light = malloc(sizeof(t_ambient));
	if (!scene->ambient_light)
		return ;
	scene->ambient_light->ratio = atof(parts[1]);
	scene->ambient_light->color = parse_color(parts[2]);
}

void	parse_camera(char **parts, t_scene *scene)
{
	if (!parts || !parts[1] || !parts[2] || !parts[3])
		return ;
	scene->camera.position = parse_vec3(parts[1]);
	scene->camera.orientation = parse_vec3(parts[2]);
	scene->camera.fov = atoi(parts[3]);
}

void	parse_light(char **parts, t_scene *scene)
{
	t_light	*light;

	if (!parts || !parts[1] || !parts[2] || !parts[3])
		return ;
	light = malloc(sizeof(t_light));
	if (!light)
		return ;
	light->position = parse_vec3(parts[1]);
	light->ratio = atof(parts[2]);
	light->color = parse_color(parts[3]);
	light->next = scene->lights;
	scene->lights = light;
}
