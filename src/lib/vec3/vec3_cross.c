/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_cross.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:04:58 by yoshin            #+#    #+#             */
/*   Updated: 2025/11/03 21:04:58 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

/*
 * vec3_cross - 두 3차원 벡터의 외적(Cross Product) 연산
 * @v1: 첫 번째 벡터
 * @v2: 두 번째 벡터
 *
 * 두 벡터에 모두 수직인 벡터를 계산합니다.
 * 외적의 크기는 두 벡터가 이루는 평행사변형의 넓이와 같습니다.
 * 외적은 교환법칙이 성립하지 않습니다: v1 × v2 = -(v2 × v1)
 * 
 * 계산 공식:
 * result.x = v1.y * v2.z - v1.z * v2.y
 * result.y = v1.z * v2.x - v1.x * v2.z
 * result.z = v1.x * v2.y - v1.y * v2.x
 *
 * Return: 외적 결과 벡터 (v1과 v2에 수직)
 */
t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}
