/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:04:16 by yoshin            #+#    #+#             */
/*   Updated: 2025/11/03 21:04:16 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>

# define WIDTH 800
# define HEIGHT 600
# define OBJ_SPHERE 1
# define OBJ_PLANE 2
# define OBJ_CYLINDER 3

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	orientation;
	int		fov;
}	t_camera;

typedef struct s_light
{
	t_vec3			position;
	double			ratio;
	t_vec3			color;
	struct s_light	*next;
}	t_light;

typedef struct s_object
{
	void			*object;
	int				type;
	t_vec3			color;
	struct s_object	*next;
}	t_object;

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	axis;
	double	diameter;
	double	height;
}	t_cylinder;

typedef struct s_scene
{
	t_camera	camera;
	t_light		*lights;
	t_object	*objects;
	t_light		*ambient_light;
}	t_scene;

typedef struct s_hit
{
	double		t;
	t_vec3		point;
	t_vec3		normal;
	t_object	*object;
}	t_hit;

typedef struct s_mlx_data
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*img_data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_mlx_data;

t_scene		*parse_scene(char *filename);
t_vec3		parse_vec3(char *str);
void		parse_ambient(char **parts, t_scene *scene);
void		parse_camera(char **parts, t_scene *scene);
void		parse_light(char **parts, t_scene *scene);
void		parse_sphere(char **parts, t_scene *scene);
void		parse_plane(char **parts, t_scene *scene);
void		parse_cylinder(char **parts, t_scene *scene);

t_ray		get_ray(t_camera camera, int i, int j, int w);
double		intersect_sphere(t_ray ray, t_sphere *sphere);
double		intersect_plane(t_ray ray, t_plane *plane);
double		intersect_cylinder(t_ray ray, t_cylinder *cylinder);
t_hit		find_closest_intersection(t_scene *scene, t_ray ray);
t_vec3		calculate_lighting(t_scene *scene, t_hit hit);
void		render_scene(t_scene *scene, t_mlx_data *data);

t_mlx_data	*init_mlx(void);
void		display_image(t_mlx_data *data);
int			close_window(t_mlx_data *data);

int			vec3_to_color(t_vec3 color);
void		free_scene(t_scene *scene);
void		save_to_bmp(t_mlx_data *data, char *filename);

#endif
