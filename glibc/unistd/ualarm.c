#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void handler(void)
{
	printf("time up\n");
}

int main(void)
{
	int i = 0;
	int rev;

	signal(SIGALRM, (__sighandler_t)handler);

	rev = ualarm(999999, 500000);
	if (rev == -1) {
		perror("ualarm:");
		exit(1);
	}

	while (1) {
		sleep(1);
		printf("i = %d\n", i++);
	}

	return 0;
}

