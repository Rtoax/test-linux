#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


int main(void)
{
	char *oldpwd, *listenq, *c_include_path;

	oldpwd = getenv("OLDPWD");
	listenq = getenv("LISTENQ");
	/* can't get GCC env C_INCLUDE_PATH */
	c_include_path = getenv("C_INCLUDE_PATH");

	printf("OLDPWD = %s\n", oldpwd);
	printf("LISTENQ = %s\n", listenq);
	printf("C_INCLUDE_PATH = %s\n", c_include_path);

	return 0;
}
