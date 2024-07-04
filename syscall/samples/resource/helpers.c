#include <stdio.h>
#include <sys/resource.h>
#include "helpers.h"

void print_rlimit(const char *prefix, struct rlimit *rlimit)
{
	printf("%s : %ld %ld\n", prefix, rlimit->rlim_cur, rlimit->rlim_max);
}

void print_rusage(const struct rusage *rusage)
{
	printf ("CPU time: %ld.%06ld sec user, %ld.%06ld sec system\n",
		rusage->ru_utime.tv_sec, rusage->ru_utime.tv_usec,
		rusage->ru_stime.tv_sec, rusage->ru_stime.tv_usec);
	printf("maxrss = %ld\n", rusage->ru_maxrss);
	printf("ixrss = %ld\n", rusage->ru_ixrss);
	printf("isrss = %ld\n", rusage->ru_isrss);
	printf("idrss = %ld\n", rusage->ru_idrss);
}
