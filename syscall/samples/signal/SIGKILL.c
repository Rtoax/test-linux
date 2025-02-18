/**
 * SIGKILL
 *
 * The default action for a process receiving SIGKILL is to terminate
 * immediately.
 * Processes cannot handle SIGKILL. It cannot be caught, blocked, or ignored by
 * the process.
 */
#include <signal.h>

int main(void)
{
	return 0;
}
