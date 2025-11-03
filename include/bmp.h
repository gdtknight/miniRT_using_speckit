/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:52:20 by yoshin            #+#    #+#             */
/*   Updated: 2025/11/03 22:52:20 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# pragma pack(push, 1)

typedef struct s_bmp_header
{
	unsigned short	type;
	unsigned int	size;
	unsigned short	reserved1;
	unsigned short	reserved2;
	unsigned int	offset;
}	t_bmp_header;

typedef struct s_bmp_info
{
	unsigned int	size;
	int				width;
	int				height;
	unsigned short	planes;
	unsigned short	bit_count;
	unsigned int	compression;
	unsigned int	size_image;
	int				x_pixels_per_meter;
	int				y_pixels_per_meter;
	int				clr_used;
	int				clr_important;
}	t_bmp_info;

# pragma pack(pop)

#endif
