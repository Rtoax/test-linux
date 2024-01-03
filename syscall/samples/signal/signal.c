#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t keep_going = 1;

void sig_handler(int signum)
{
	psignal(signum, "Signal");

	switch (signum) {
	case SIGINT:
		keep_going = 0;
		break;
	case SIGALRM:
		printf("Get SIGALRM.\n");
		break;
	}
}

int main(void)
{
	sighandler_t sighandler;

	signal(SIGINT, sig_handler);
	sighandler = signal(SIGALRM, sig_handler);
	if (sighandler == SIG_ERR) {
		printf("signal SIGALRM failed.\n");
	}

	while (keep_going) {
		sleep(1);
		alarm(1);
	}

	return 0;
}
