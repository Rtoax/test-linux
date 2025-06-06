#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>


void handler(int signum)
{
	printf("Get signal %s\n", strsignal(signum));
	exit(1);
}

int main(void)
{
	signal(SIGINT, handler);

	while (1) {
		printf("main loop\n");
		killpg(getpid(), SIGINT);
	}

	return 0;
}
