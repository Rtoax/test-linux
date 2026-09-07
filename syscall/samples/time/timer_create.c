/**
 * timer_gettime(2): Fetch the time remaining until the next expiration of a
 * timer, along with the interval setting of the timer.
 */
#include <signal.h>
#include <time.h>
#include <stdio.h>

int main(void)
{
	struct itimerspec it;
	timer_t timerid;
	struct sigevent sev;

	timer_create(CLOCK_REALTIME, &sev, &timerid);
	timer_gettime(timerid, &it);

	return 0;
}
