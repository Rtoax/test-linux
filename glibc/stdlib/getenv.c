#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


int main(void)
{
	char *env = getenv("OLDPWD");
	char *listenq = getenv("LISTENQ");
	/* can't get GCC env C_INCLUDE_PATH */
	char *c_include_path = getenv("C_INCLUDE_PATH");

	printf("env = %s\n", env);
	printf("listenq = %s\n", listenq);
	printf("C_INCLUDE_PATH = %s\n", c_include_path);

	return 0;
}
