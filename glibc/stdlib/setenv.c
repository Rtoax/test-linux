#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	char *env;

	setenv("HOME_RONGTAO", "/home/rongtao", 1);
	env = getenv("HOME_RONGTAO");
	printf("env = %s\n", env);

	return 0;
}