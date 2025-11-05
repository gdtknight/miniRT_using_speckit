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

/*
 * check_args - 커맨드 라인 인자 검증
 * @argc: 인자 개수
 *
 * 프로그램 실행 시 올바른 인자가 제공되었는지 확인합니다.
 * 사용법: ./miniRT <scene.rt>
 *
 * Return: 1 (성공), 0 (실패)
 */
static int	check_args(int argc)
{
	if (argc != 2)
	{
		printf("Error\nUsage: ./miniRT <scene.rt>\n");
		return (0);
	}
	return (1);
}

/*
 * init_scene - 장면 파일 파싱 및 초기화
 * @filename: .rt 장면 파일 경로
 *
 * 장면 파일을 읽어서 파싱하고 내부 데이터 구조로 변환합니다.
 * 장면 파일에는 다음 정보가 포함됩니다:
 * - A: 환경광 (Ambient light)
 * - C: 카메라 (Camera)
 * - L: 광원 (Light)
 * - sp: 구 (Sphere)
 * - pl: 평면 (Plane)
 * - cy: 원기둥 (Cylinder)
 *
 * Return: 파싱된 장면 구조체, 실패 시 NULL
 */
static t_scene	*init_scene(char *filename)
{
	t_scene	*scene;

	printf("Parsing scene: %s\n", filename);
	scene = parse_scene(filename);
	if (!scene)
		return (NULL);
	return (scene);
}

/*
 * init_and_render - MLX 초기화 및 렌더링 수행
 * @scene: 렌더링할 장면
 *
 * MiniLibX를 초기화하고 레이트레이싱을 수행합니다.
 *
 * 동작 과정:
 * 1. MLX 초기화 (창, 이미지 버퍼 생성)
 * 2. 장면 렌더링 (render_scene)
 *    - 모든 픽셀에 대해 레이트레이싱 수행
 * 3. BMP 파일로 저장 (output.bmp)
 *
 * Return: 초기화된 MLX 데이터, 실패 시 NULL
 */
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

/*
 * main - 프로그램 진입점
 * @argc: 인자 개수
 * @argv: 인자 배열
 *
 * miniRT 레이트레이서의 메인 함수입니다.
 *
 * 실행 흐름:
 * 1. 커맨드 라인 인자 검증
 * 2. 장면 파일 파싱
 * 3. MLX 초기화 및 렌더링
 * 4. 이벤트 핸들러 등록
 *    - 키보드 입력 (ESC로 종료)
 *    - 창 닫기 이벤트
 *    - 화면 갱신 이벤트
 * 5. 이벤트 루프 시작 (창 유지)
 *
 * 이벤트:
 * - EVENT_CLOSE: 창 닫기 버튼 클릭
 * - EVENT_EXPOSE: 창이 다시 보여질 때 (가려졌다가 다시 나타남)
 * - KEY_ESC: ESC 키로 프로그램 종료
 *
 * Return: 0 (성공), 1 (실패)
 */
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
	mlx_loop_hook(data->mlx, (int (*)(void *))loop_hook, data);
	mlx_key_hook(data->win, handle_key, data);
	mlx_hook(data->win, EVENT_CLOSE, 0, close_window, data);
	mlx_hook(data->win, EVENT_EXPOSE, 0, expose_hook, data);
	mlx_loop(data->mlx);
	return (0);
}
