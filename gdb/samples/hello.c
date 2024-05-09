#include <stdio.h>

union utest {
	int i;
	char c[4];
};

struct stest {
	int i;
	struct stest *parent;
};

int global_i = 10;
union utest ut1;
struct stest st1;

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
