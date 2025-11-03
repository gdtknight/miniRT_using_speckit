/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:18:47 by yoshin            #+#    #+#             */
/*   Updated: 2025/11/03 22:18:47 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include "minirt.h"

t_vec3	vec3_new(double x, double y, double z);
t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_mul(t_vec3 v, double t);
t_vec3	vec3_div(t_vec3 v, double t);
double	vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2);
double	vec3_length(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);

#endif
