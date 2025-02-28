#include <stdio.h>
#include <stdlib.h>

/* The ENVIRON variable contains the environment. */
extern char **environ;

int main(void)
{
	char **var;

	printf("environ address %p\n", environ);

	setenv("MY_NAME", "Rong Tao", 1);

	for (var = environ; *var != NULL; ++var)
		printf ("%s\n", *var);

	return 0;
}
