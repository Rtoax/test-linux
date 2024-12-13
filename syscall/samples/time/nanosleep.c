#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#include "helpers.h"


int better_sleep(double s)
{
	struct timespec ts;

	ts.tv_sec = (time_t)s;
	ts.tv_nsec = (long)((s - ts.tv_sec) * 1e+9);

	while (1) {
		int rval = nanosleep(&ts, &ts);
		if (rval == 0)
			return 0;
		/* Interrupted by a signal. Try again. */
		else if (errno == EINTR)
			continue;
		else
			return rval;
	}
	return 0;
}

int main(void)
{
	struct timespec ts = {1, 0};
	nanosleep(&ts, NULL);
	better_sleep(1.001);
	sys_nanosleep(&ts, NULL);
	return 0;
}

