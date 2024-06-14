#include <signal.h>
#include <stdio.h>

volatile sig_atomic_t flag = 0;

int main(void)
{
	sigset_t block_alarm;

	/* Initialize the signal mask. */
	sigemptyset(&block_alarm);
	sigaddset(&block_alarm, SIGALRM);

	while (1) {
		/* Check if a signal has arrived; if so, reset the flag. */
		sigprocmask(SIG_BLOCK, &block_alarm, NULL);
		if (flag) {
			/* actions-if-not-arrived */
			printf("flag = 0.\n");
			flag = 0;
		}
		sigprocmask(SIG_UNBLOCK, &block_alarm, NULL);
	}

	return 0;
}

