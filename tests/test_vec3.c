#include "vec3.h"
#include <stdio.h>
#include <assert.h>

void	test_vec3_add()
{
	t_vec3	v1 = {1, 2, 3};
	t_vec3	v2 = {4, 5, 6};
	t_vec3	result = vec3_add(v1, v2);
	assert(result.x == 5);
	assert(result.y == 7);
	assert(result.z == 9);
	printf("test_vec3_add: OK\n");
}

void	test_vec3_sub()
{
	t_vec3	v1 = {4, 5, 6};
	t_vec3	v2 = {1, 2, 3};
	t_vec3	result = vec3_sub(v1, v2);
	assert(result.x == 3);
	assert(result.y == 3);
	assert(result.z == 3);
	printf("test_vec3_sub: OK\n");
}

// Add more tests for other functions...

