#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


int main(void)
{
	char *env = getenv("OLDPWD");
	char *listenq = getenv("LISTENQ");

	printf("env = %s\n", env);
	printf("listenq = %s\n", listenq);

	return 0;
}
