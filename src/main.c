/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:04:15 by yoshin            #+#    #+#             */
/*   Updated: 2025/11/03 21:04:15 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <mlx.h>

int	handle_key(int keycode, t_mlx_data *data);

static int	check_args(int argc)
{
	if (argc != 2)
	{
		printf("Error\nUsage: ./miniRT <scene.rt>\n");
		return (0);
	}
	return (1);
}

static t_scene	*init_scene(char *filename)
{
	t_scene	*scene;

	printf("Parsing scene: %s\n", filename);
	scene = parse_scene(filename);
	if (!scene)
	{
		printf("Error\nFailed to parse scene file\n");
		return (NULL);
	}
	return (scene);
}

static t_mlx_data	*init_and_render(t_scene *scene)
{
	t_mlx_data	*data;

	printf("Initializing MLX...\n");
	data = init_mlx();
	if (!data)
	{
		printf("Error\nFailed to initialize MLX\n");
		return (NULL);
	}
	printf("Rendering scene...\n");
	render_scene(scene, data);
	printf("Saving to output.bmp...\n");
	save_to_bmp(data, "output.bmp");
	return (data);
}

int	main(int argc, char **argv)
{
	t_scene		*scene;
	t_mlx_data	*data;

	if (!check_args(argc))
		return (1);
	scene = init_scene(argv[1]);
	if (!scene)
		return (1);
	data = init_and_render(scene);
	if (!data)
		return (1);
	printf("Done! Displaying (ESC to exit).\n");
	display_image(data);
	mlx_key_hook(data->win, handle_key, data);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop(data->mlx);
	return (0);
}
