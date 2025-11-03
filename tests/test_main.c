#include <stdio.h>

void	test_vec3_add();
void	test_vec3_sub();
void	test_parse_ambient();
void	test_parse_camera();

int	main()
{
	printf("--- Running tests ---\n");
	test_vec3_add();
	test_vec3_sub();
	test_parse_ambient();
	test_parse_camera();
	printf("--- All tests passed ---\n");
	return (0);
}
