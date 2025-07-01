// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <stdio.h>
#include <sys/resource.h>
#include "resource_helpers.h"

void print_rlimit(const char *prefix, struct rlimit *rlimit)
{
	/**
	 * rlim_cur is soft limit
	 * rlim_max is hard limit
	 *
	 * see also pam:/etc/security/limits.conf
	 */
	printf("%s : soft:%ld hard:%ld\n", prefix, rlimit->rlim_cur,
		rlimit->rlim_max);
}

void print_rusage(const char *prefix, const struct rusage *rusage)
{
	printf ("%-8sCPU time: %ld.%06ld sec user, %ld.%06ld sec system\n",
		prefix,
		rusage->ru_utime.tv_sec, rusage->ru_utime.tv_usec,
		rusage->ru_stime.tv_sec, rusage->ru_stime.tv_usec);
	printf("%-8smaxrss: %ld (memory usage KB)\n", prefix, rusage->ru_maxrss);
	printf("%-8sru_ixrss: %ld\n", prefix, rusage->ru_ixrss);
	printf("%-8sru_idrss: %ld\n", prefix, rusage->ru_idrss);
	printf("%-8sru_isrss: %ld\n", prefix, rusage->ru_isrss);
	printf("%-8sru_minflt: %ld\n", prefix, rusage->ru_minflt);
	printf("%-8sru_majflt: %ld\n", prefix, rusage->ru_majflt);
	printf("%-8sru_nswap: %ld\n", prefix, rusage->ru_nswap);
	printf("%-8sru_inblock: %ld\n", prefix, rusage->ru_inblock);
	printf("%-8sru_oublock: %ld\n", prefix, rusage->ru_oublock);
	printf("%-8sru_msgsnd: %ld\n", prefix, rusage->ru_msgsnd);
	printf("%-8sru_msgrcv: %ld\n", prefix, rusage->ru_msgrcv);
	printf("%-8sru_nsignals: %ld\n", prefix, rusage->ru_nsignals);
	printf("%-8sru_nvcsw: %ld\n", prefix, rusage->ru_nvcsw);
	printf("%-8sru_nivcsw: %ld\n", prefix, rusage->ru_nivcsw);
}
