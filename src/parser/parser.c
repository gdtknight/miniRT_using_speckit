/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniRT <miniRT@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:00:00 by miniRT           #+#    #+#             */
/*   Updated: 2025/11/03 00:00:00 by miniRT          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

/*
 * free_parts - 문자열 배열 메모리 해제
 * @parts: ft_split으로 생성된 문자열 배열
 *
 * ft_split으로 동적 할당된 문자열 배열을 완전히 해제합니다.
 * 1. 각 문자열 요소 해제
 * 2. 배열 자체 해제
 *
 * NULL 포인터 안전성을 보장합니다.
 */
static void	free_parts(char **parts)
{
	int	i;

	if (!parts)
		return ;
	i = 0;
	while (parts[i])
	{
		free(parts[i]);
		i++;
	}
	free(parts);
}

/*
 * parse_line - 장면 파일의 한 줄을 파싱
 * @line: 파싱할 한 줄의 문자열
 * @scene: 파싱 결과를 저장할 장면 구조체
 *
 * 장면 파일의 각 줄은 공백으로 구분된 토큰들로 이루어져 있습니다.
 * 첫 번째 토큰(식별자)에 따라 적절한 파서 함수를 호출합니다.
 *
 * 지원하는 요소:
 * - A: 환경광 (Ambient light) - 1개만
 * - C: 카메라 (Camera) - 1개만
 * - L: 광원 (Light) - 여러 개 가능
 * - sp: 구 (Sphere)
 * - pl: 평면 (Plane)
 * - cy: 원기둥 (Cylinder)
 *
 * 형식 예:
 * A 0.2 255,255,255
 * C 0,0,0 0,0,1 70
 * L -40,0,30 0.7 255,255,255
 * sp 0,0,20 20 255,0,0
 * pl 0,0,0 0,1,0 255,255,255
 */
void	parse_line(char *line, t_scene *scene)
{
	char	**parts;

	parts = ft_split(line, ' ');
	if (!parts || !parts[0])
	{
		free_parts(parts);
		return ;
	}
	if (parts[0][0] == 'A' && !parts[0][1])
		parse_ambient(parts, scene);
	else if (parts[0][0] == 'C' && !parts[0][1])
		parse_camera(parts, scene);
	else if (parts[0][0] == 'L' && !parts[0][1])
		parse_light(parts, scene);
	else if (parts[0][0] == 's' && parts[0][1] == 'p' && !parts[0][2])
		parse_sphere(parts, scene);
	else if (parts[0][0] == 'p' && parts[0][1] == 'l' && !parts[0][2])
		parse_plane(parts, scene);
	else if (parts[0][0] == 'c' && parts[0][1] == 'y' && !parts[0][2])
		parse_cylinder(parts, scene);
	free_parts(parts);
}

/*
 * init_scene - 빈 장면 구조체 초기화
 *
 * 장면 구조체를 메모리에 할당하고 모든 필드를 NULL로 초기화합니다.
 * 파싱 과정에서 각 요소가 추가됩니다.
 *
 * 초기 상태:
 * - objects: NULL (물체 목록 비어있음)
 * - lights: NULL (광원 목록 비어있음)
 * - ambient_light: NULL (아직 파싱 안됨)
 * - camera: 파싱될 때까지 정의되지 않음
 *
 * Return: 할당된 장면 구조체, 실패 시 NULL
 */
static t_scene	*init_scene(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->objects = NULL;
	scene->lights = NULL;
	scene->ambient_light = NULL;
	return (scene);
}

/*
 * parse_buffer_lines - 버퍼를 줄 단위로 파싱
 * @buffer: 파일에서 읽은 전체 내용
 * @bytes: 버퍼의 유효한 바이트 수
 * @scene: 파싱 결과를 저장할 장면 구조체
 *
 * 버퍼를 개행 문자('\n')로 구분하여 각 줄을 파싱합니다.
 *
 * 처리 과정:
 * 1. 개행 문자를 찾으면 NULL 문자로 대체
 * 2. 줄이 비어있지 않고 주석('#')이 아니면 파싱
 * 3. 다음 줄로 이동
 *
 * 주석 처리:
 * - '#'로 시작하는 줄은 무시됨
 * - 빈 줄도 무시됨
 *
 * 줄바꿈 없이 끝나는 파일도 처리합니다 (i == bytes 조건).
 */
static void	parse_buffer_lines(char *buffer, ssize_t bytes, t_scene *scene)
{
	int	start;
	int	i;

	start = 0;
	i = 0;
	while (i <= bytes)
	{
		if (i == bytes || buffer[i] == '\n')
		{
			buffer[i] = '\0';
			if (buffer[start] && buffer[start] != '#')
				parse_line(&buffer[start], scene);
			start = i + 1;
		}
		i++;
	}
}

/*
 * parse_scene - 장면 파일을 파싱하여 장면 구조체 생성
 * @filename: .rt 장면 파일 경로
 *
 * 장면 파일을 읽어서 완전한 장면 구조체로 변환합니다.
 *
 * 동작 과정:
 * 1. 파일 열기 (읽기 전용)
 * 2. 빈 장면 구조체 초기화
 * 3. 파일 내용을 버퍼로 읽기 (최대 1023바이트)
 * 4. 버퍼를 줄 단위로 파싱
 * 5. 파일 닫기
 *
 * 제한사항:
 * - 파일 크기는 1KB 미만이어야 함
 * - 더 큰 파일은 잘림
 *
 * 개선 가능성:
 * - 동적 버퍼 크기 조정
 * - 여러 번 읽기로 큰 파일 지원
 * - 더 상세한 에러 메시지
 *
 * Return: 파싱된 장면 구조체, 실패 시 NULL
 */
t_scene	*parse_scene(char *filename)
{
	int			fd;
	char		buffer[1024];
	t_scene		*scene;
	ssize_t		bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\n");
		return (NULL);
	}
	scene = init_scene();
	if (!scene)
	{
		printf("Error\n");
		close(fd);
		return (NULL);
	}
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		parse_buffer_lines(buffer, bytes_read, scene);
	}
	close(fd);
	return (scene);
}
