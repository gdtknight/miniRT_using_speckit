/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:52:20 by yoshin            #+#    #+#             */
/*   Updated: 2025/11/03 22:52:20 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <mlx.h>

void	display_image(t_mlx_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int	close_window(t_mlx_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

int	handle_key(int keycode, t_mlx_data *data)
{
	if (keycode == 53)
		close_window(data);
	return (0);
}
