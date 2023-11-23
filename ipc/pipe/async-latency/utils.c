#include <libgen.h>
#include "utils.h"


int gettimeval(struct timeval *tv)
{
	return gettimeofday(tv, NULL);
}

double statistic_throughput(char *description, struct timeval *before,
		struct timeval *after, unsigned long int bytes, long int npkg)
{
	double us = (after->tv_sec - before->tv_sec) * 1000000.0 + \
			after->tv_usec - before->tv_usec;
	double Mbps = 8 * bytes * 1.0 / us;
	printf("-- %s: Total %.3lf Mbps, bytes = %ld(bits:%ld), npkg = %ld.\n",
		description ?: "Unknown Description",
		Mbps, bytes, bytes * 8, npkg);
	return Mbps;
}

int ___debug_log(int level, char *file, const char *func, int line, char *fmt, ...)
{
	int i;
	va_list av;
	va_start(av, fmt);

	switch (level) {
	case __LV_INFO:
		printf(" [%s INFO%s][%s:%s:%d]: ","\033[1;36m","\033[0m", basename(file), func, line);
		break;
	case __LV_WARNING:
		printf(" [%s WARN%s][%s:%s:%d]: ","\033[1;35m","\033[0m", basename(file), func, line);
		break;
	case __LV_ERR:
		printf("[%sERROR%s][%s:%s:%d]: ","\033[1;31m","\033[0m", basename(file), func, line);
		break;
	case __LV_DEBUG:
		printf("[%sDEBUG%s][%s:%s:%d]: ","\033[1m",   "\033[0m", basename(file), func, line);
		break;
	}

	i = vprintf(fmt, av);

	va_end(av);

	return i;
}

