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
	printf("maxrss: %ld\n", rusage->ru_maxrss);
	printf("ru_ixrss: %ld\n", rusage->ru_ixrss);
	printf("ru_idrss: %ld\n", rusage->ru_idrss);
	printf("ru_isrss: %ld\n", rusage->ru_isrss);
	printf("ru_minflt: %ld\n", rusage->ru_minflt);
	printf("ru_majflt: %ld\n", rusage->ru_majflt);
	printf("ru_nswap: %ld\n", rusage->ru_nswap);
	printf("ru_inblock: %ld\n", rusage->ru_inblock);
	printf("ru_oublock: %ld\n", rusage->ru_oublock);
	printf("ru_msgsnd: %ld\n", rusage->ru_msgsnd);
	printf("ru_msgrcv: %ld\n", rusage->ru_msgrcv);
	printf("ru_nsignals: %ld\n", rusage->ru_nsignals);
	printf("ru_nvcsw: %ld\n", rusage->ru_nvcsw);
	printf("ru_nivcsw: %ld\n", rusage->ru_nivcsw);
}
