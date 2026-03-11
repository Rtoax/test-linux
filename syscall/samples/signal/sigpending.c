#include <signal.h>
#include <stdio.h>
#include <signal.h>
#include <stddef.h>
#include <unistd.h>

void print_pending(void)
{
	sigset_t waiting_mask;
	/* After a while, check to see whether any signals are pending. */
	sigpending(&waiting_mask);

	/* ctrl-C */
	if (sigismember(&waiting_mask, SIGINT)) {
		/* User has tried to kill the process. */
		printf("SIGINT\n");
	}
	/* ctrl-Z */
	if (sigismember(&waiting_mask, SIGTSTP)) {
		/* User has tried to stop the process. */
		printf("SIGTSTP\n");
	}
}

int main(void)
{
	sigset_t base_mask;

	sigemptyset(&base_mask);
	sigaddset(&base_mask, SIGINT);
	sigaddset(&base_mask, SIGTSTP);
	/* Block user interrupts while doing other processing. */
	sigprocmask(SIG_SETMASK, &base_mask, NULL);

	while (1) {
		sleep(1);
		print_pending();
	}

	return 0;
}
