/**
 * SIGTERM
 *
 * The default action for a process receiving SIGTERM is to terminate.
 * Processes can handle SIGTERM by defining a signal handler. This allows the
 * process to perform cleanup tasks, such as closing files or releasing
 * resources, before exiting.
 */
#include <signal.h>

void sig_handler(int signum)
{
	psignal(signum, "Signal");
}

int main(void)
{
	signal(SIGTERM, sig_handler);

	sleep(100);

	return 0;
}
