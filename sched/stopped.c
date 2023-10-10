/**
 * Give me a SIGSTOP signal with 'kill -19 PID', and wake with 'kill -18 PID'
 *
 * There are two different stop type: see ps(1)
 * T    stopped by job control signal
 * t    stopped by debugger during the tracing
 *
 * Check process stat with:
 * $ ps -e -w -o stat,pid,lstart,comm
 */
#include <unistd.h>

int main(void)
{
	pause();
	return 0;
}
