#include <errno.h>
#include "vdso.h"

int vdso_clock_gettime(clockid_t clockid, struct timespec *res)
{
	if (!res)
		return -EINVAL;
	res->tv_sec = 1;
	res->tv_nsec = 1;
	return 0;
}

int vdso_gettimeofday(struct timeval *tv, struct timezone *tz)
{
	if (!tv)
		return -EINVAL;
	tv->tv_sec = 1;
	tv->tv_usec = 1;
	return 0;
}
