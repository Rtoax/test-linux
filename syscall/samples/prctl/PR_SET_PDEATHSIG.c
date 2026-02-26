#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/prctl.h>

void sig_handler(int sig)
{
	psignal(sig, "Getting");
	exit(1);
}

int main(void)
{
	int pid = fork();

	signal(SIGINT, sig_handler);

	if (pid == 0) {
		/**
		 * This is the signal that the calling process will get when
		 * its parent dies.
		 */
		prctl(PR_SET_PDEATHSIG, SIGINT);

		for (;;) {
			printf("Child sleeping...\n");
			sleep(1);
		}
		exit(1);
	}

	sleep(1);
	printf("Parent exiting.\n");

	return 0;
}
