#include <stdio.h>
#include <stdlib.h>

/* The ENVIRON variable contains the environment. */
extern char **environ;

void display_environ(void)
{
	for (char **var = environ; *var != NULL; ++var)
		printf("%s\n", *var);
}

int main(void)
{
	printf("environ address %p\n", environ);

	display_environ();
	setenv("MY_NAME", "Rong Tao", 1);
	display_environ();

	return 0;
}
