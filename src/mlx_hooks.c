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

/*
 * display_image - 이미지를 창에 표시
 * @data: MLX 데이터 (창, 이미지 포함)
 *
 * 렌더링된 이미지를 MLX 창에 표시합니다.
 * img_displayed 플래그를 설정하여 중복 표시를 방지합니다.
 */
void	display_image(t_mlx_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	data->img_displayed = 1;
}

/*
 * loop_hook - 메인 이벤트 루프 훅
 * @data: MLX 데이터
 *
 * MLX의 메인 루프에서 매 프레임마다 호출됩니다.
 * 아직 이미지가 표시되지 않았으면 표시합니다.
 * 
 * 이 함수는 프로그램 시작 시 한 번만 이미지를 표시하고,
 * 이후에는 아무 작업도 하지 않습니다.
 *
 * Return: 0 (계속 실행)
 */
int	loop_hook(t_mlx_data *data)
{
	if (!data->img_displayed)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
		data->img_displayed = 1;
	}
	return (0);
}

/*
 * expose_hook - 창 노출 이벤트 핸들러
 * @data: MLX 데이터
 *
 * 창이 가려졌다가 다시 보이거나, 최소화 후 복원될 때 호출됩니다.
 * 이미지를 다시 그려서 화면을 복구합니다.
 *
 * Return: 0
 */
int	expose_hook(t_mlx_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

/*
 * close_window - 창 닫기 이벤트 핸들러
 * @data: MLX 데이터
 *
 * 창의 X 버튼을 클릭하거나 프로그램을 종료할 때 호출됩니다.
 * 
 * 정리 작업:
 * 1. 이미지 메모리 해제
 * 2. 창 파괴
 * 3. 프로그램 종료
 *
 * Return: 0 (실제로는 exit로 종료됨)
 */
int	close_window(t_mlx_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

/*
 * handle_key - 키보드 입력 이벤트 핸들러
 * @keycode: 눌린 키의 코드
 * @data: MLX 데이터
 *
 * 키보드 입력을 처리합니다.
 * 현재는 ESC 키만 처리하여 프로그램을 종료합니다.
 *
 * 확장 가능성:
 * - 방향키로 카메라 이동
 * - 숫자 키로 다른 장면 로드
 * - 스페이스바로 렌더링 재시작
 *
 * Return: 0
 */
int	handle_key(int keycode, t_mlx_data *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	return (0);
}
