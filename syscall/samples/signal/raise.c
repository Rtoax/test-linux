#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int signum)
{
	printf("RongTao\n");
	exit(1);
}

int main(int argc, char *argv[])
{
	signal(SIGINT, handler);

	while (1) {
		printf("main loop\n");
		raise(SIGKILL);
	}

	return 0;
}
