#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void sig_handler(int signum)
{
	/* Click ctrl-c twice */
	psignal(signum, "Get signal again");
	exit(0);
}

int main(void)
{
	sighandler_t sighandler;
	sigset_t sigset;
	int signum;

	sighandler = signal(SIGINT, sig_handler);
	if (sighandler == SIG_ERR) {
		printf("signal SIGALRM failed.\n");
	}

	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);

	printf("Waiting signal...\n");

	/* Click ctrl-c once */
	sigwait(&sigset, &signum);

	psignal(signum, "Get signal");

	sleep(1);

	return 0;
}
