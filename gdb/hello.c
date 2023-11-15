#include <stdio.h>

int hello(void)
{
	return printf("Hello %s.\n", "World");
}

int main(int argc, char *argv[])
{
	int ret;

	if (argc > 1) {
		int i;
		for (i = 1; i < argc; i++)
			printf("%s ", argv[i]);
		printf("\n");
	}
	ret = hello();
	return ret;
}
