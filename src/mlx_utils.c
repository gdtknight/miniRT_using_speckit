/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:04:21 by yoshin            #+#    #+#             */
/*   Updated: 2025/11/03 21:04:21 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <mlx.h>

static int	init_mlx_connection(t_mlx_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	if (!data->win)
		return (0);
	return (1);
}

static int	init_mlx_image(t_mlx_data *data)
{
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
		return (0);
	data->img_data = (int *)mlx_get_data_addr(data->img,
			&data->bpp, &data->size_line, &data->endian);
	return (1);
}

t_mlx_data	*init_mlx(void)
{
	t_mlx_data	*data;

	data = malloc(sizeof(t_mlx_data));
	if (!data)
		return (NULL);
	if (!init_mlx_connection(data))
	{
		free(data);
		return (NULL);
	}
	if (!init_mlx_image(data))
	{
		free(data);
		return (NULL);
	}
	return (data);
}
