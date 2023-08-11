#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	char *env;

	setenv("RongTao", "/home/rongtao", 1);

	env = getenv("RongTao");
	printf("env = %s\n", env);
	unsetenv("RongTao");

	env = getenv("RongTao");
	printf("env = %s (unset)\n", env);

	return 0;
}
