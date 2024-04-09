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


