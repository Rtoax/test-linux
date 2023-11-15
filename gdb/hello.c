#include <stdio.h>

int global_i = 10;

int hello(int argc, char *argv[])
{
	global_i++;
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
	ret = hello(argc, argv);
	return ret + global_i;
}
