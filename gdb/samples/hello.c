#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

union utest {
	int i;
	char c[4];
};

struct stest {
	int i;
	struct stest *parent;
};

int data_global_i = 10;
const int rodata_global_i = 10;
int bss_global_i = 0;

union utest ut1;
struct stest st1;

void sig_handler(int sig)
{
	psignal(sig, "Get");
	exit(1);
}

int hello(int argc, char *argv[])
{
	data_global_i++;
	return printf("Hello %s.\n", "World");
}

static int static_hello(int argc, char *argv[])
{
	return hello(argc, argv);
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
	return ret + data_global_i;
}
