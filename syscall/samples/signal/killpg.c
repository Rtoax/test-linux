#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


void handler(int signum)
{
	printf("Get signal\n");
	exit(1);
}

int main()
{
	signal(SIGINT, handler);

	while (1) {
		printf("main loop\n");
		killpg(getpid(), SIGINT);
	}

	return 0;
}
