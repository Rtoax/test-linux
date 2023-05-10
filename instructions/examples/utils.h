#pragma once

#include <sys/time.h>


void print_diff_tv(const char *name, struct timeval *end, struct timeval *start)
{
	printf("%16s: %ld us\n",
		name,
		(end->tv_sec - start->tv_sec) * 1000000
		+ (end->tv_usec - start->tv_usec));
}
