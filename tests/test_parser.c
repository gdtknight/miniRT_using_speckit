#include "minirt.h"
#include <stdio.h>
#include <assert.h>

void	parse_line(char *line, t_scene *scene);

void	test_parse_ambient()
{
	t_scene	scene = {0};
	parse_line("A 0.2 255,255,255", &scene);
	assert(scene.ambient_light->ratio == 0.2);
	assert(scene.ambient_light->color.x == 255);
	assert(scene.ambient_light->color.y == 255);
	assert(scene.ambient_light->color.z == 255);
	printf("test_parse_ambient: OK\n");
}

void	test_parse_camera()
{
	t_scene	scene = {0};
	parse_line("C -50,0,20 0,0,1 70", &scene);
	assert(scene.camera.position.x == -50);
	assert(scene.camera.fov == 70);
	printf("test_parse_camera: OK\n");
}

