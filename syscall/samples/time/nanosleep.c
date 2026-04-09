#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include "time_helpers.h"

int better_sleep(double s)
{
	int rval = 0;
	struct timespec ts;

	ts.tv_sec = (time_t)s;
	ts.tv_nsec = (long)((s - ts.tv_sec) * 1e+9);

	while (1) {
		rval = nanosleep(&ts, &ts);
		if (rval == 0)
			return 0;
		/* Interrupted by a signal. Try again. */
		else if (errno == EINTR)
			continue;
		else
			return rval;
	}
	return rval;
}

int main(void)
{
	int i;
	struct timespec tss[] = { { 1, 0 }, { -1, -2 } };

#define RET(call) printf("%s = %d\n", #call, call)
	for (i = 0; i < 2; i++) {
		RET(nanosleep(tss + i, NULL));
		RET(better_sleep(1.001));
		RET(sys_nanosleep(tss + i, NULL));
	}
#undef RET

	return 0;
}

