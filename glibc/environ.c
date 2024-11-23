#include <stdio.h>

/* The ENVIRON variable contains the environment. */
extern char **environ;

int main(void)
{
	char **var;

	printf("environ address %p\n", environ);

	for (var = environ; *var != NULL; ++var)
		printf ("%s\n", *var);

	return 0;
}
