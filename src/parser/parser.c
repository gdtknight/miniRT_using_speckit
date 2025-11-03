/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniRT <miniRT@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:00:00 by miniRT           #+#    #+#             */
/*   Updated: 2025/11/03 00:00:00 by miniRT          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

void	parse_line(char *line, t_scene *scene)
{
	char	**parts;

	parts = ft_split(line, ' ');
	if (!parts || !parts[0])
		return ;
	if (parts[0][0] == 'A' && !parts[0][1])
		parse_ambient(parts, scene);
	else if (parts[0][0] == 'C' && !parts[0][1])
		parse_camera(parts, scene);
	else if (parts[0][0] == 'L' && !parts[0][1])
		parse_light(parts, scene);
	else if (parts[0][0] == 's' && parts[0][1] == 'p' && !parts[0][2])
		parse_sphere(parts, scene);
	else if (parts[0][0] == 'p' && parts[0][1] == 'l' && !parts[0][2])
		parse_plane(parts, scene);
	else if (parts[0][0] == 'c' && parts[0][1] == 'y' && !parts[0][2])
		parse_cylinder(parts, scene);
}

static t_scene	*init_scene(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->objects = NULL;
	scene->lights = NULL;
	scene->ambient_light = NULL;
	return (scene);
}

static void	parse_buffer_lines(char *buffer, ssize_t bytes, t_scene *scene)
{
	int	start;
	int	i;

	start = 0;
	i = 0;
	while (i <= bytes)
	{
		if (i == bytes || buffer[i] == '\n')
		{
			buffer[i] = '\0';
			if (buffer[start] && buffer[start] != '#')
				parse_line(&buffer[start], scene);
			start = i + 1;
		}
		i++;
	}
}

t_scene	*parse_scene(char *filename)
{
	int			fd;
	char		buffer[1024];
	t_scene		*scene;
	ssize_t		bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	scene = init_scene();
	if (!scene)
	{
		close(fd);
		return (NULL);
	}
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		parse_buffer_lines(buffer, bytes_read, scene);
	}
	close(fd);
	return (scene);
}
