/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:04:23 by yoshin            #+#    #+#             */
/*   Updated: 2025/11/03 21:04:23 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "bmp.h"
#include <fcntl.h>
#include <unistd.h>

static void	init_bmp_header(t_bmp_header *header)
{
	header->type = 0x4D42;
	header->size = 54 + WIDTH * HEIGHT * 3;
	header->reserved1 = 0;
	header->reserved2 = 0;
	header->offset = 54;
}

static void	init_bmp_info(t_bmp_info *info)
{
	info->size = 40;
	info->width = WIDTH;
	info->height = HEIGHT;
	info->planes = 1;
	info->bit_count = 24;
	info->compression = 0;
	info->size_image = WIDTH * HEIGHT * 3;
	info->x_pixels_per_meter = 0;
	info->y_pixels_per_meter = 0;
	info->clr_used = 0;
	info->clr_important = 0;
}

static void	write_pixel_row(int fd, t_mlx_data *data, int y)
{
	int				x;
	unsigned char	pixel[3];

	x = 0;
	while (x < WIDTH)
	{
		pixel[2] = (data->img_data[y * WIDTH + x] >> 16) & 0xFF;
		pixel[1] = (data->img_data[y * WIDTH + x] >> 8) & 0xFF;
		pixel[0] = data->img_data[y * WIDTH + x] & 0xFF;
		write(fd, pixel, 3);
		x++;
	}
}

void	save_to_bmp(t_mlx_data *data, char *filename)
{
	int				fd;
	t_bmp_header	header;
	t_bmp_info		info;
	int				y;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	init_bmp_header(&header);
	init_bmp_info(&info);
	write(fd, &header, sizeof(t_bmp_header));
	write(fd, &info, sizeof(t_bmp_info));
	y = HEIGHT - 1;
	while (y >= 0)
	{
		write_pixel_row(fd, data, y);
		y--;
	}
	close(fd);
}
