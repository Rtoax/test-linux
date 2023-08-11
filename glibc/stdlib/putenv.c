#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


int main(void)
{
	char *env;

	putenv("PATH=/home/rongtao");

	env = getenv("PATH");

	printf("env = %s\n", env);

	return 0;
}
