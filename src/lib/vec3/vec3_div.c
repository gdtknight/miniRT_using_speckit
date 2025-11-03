/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_div.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:04:59 by yoshin            #+#    #+#             */
/*   Updated: 2025/11/03 21:04:59 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	vec3_div(t_vec3 v, double t)
{
	t_vec3	result;

	result.x = v.x / t;
	result.y = v.y / t;
	result.z = v.z / t;
	return (result);
}
