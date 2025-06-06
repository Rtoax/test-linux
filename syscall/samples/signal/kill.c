#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

int ret = -1;

void handler(int signum)
{
	printf("Get signal %s, ret = %d\n\n", strsignal(signum), ret);
	exit(1);
}

int main(void)
{
	signal(SIGINT, handler);

	while (1) {
		printf("123123\n");
		ret = kill(getpid(), SIGINT);
	}

	return 0;
}
