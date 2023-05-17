#pragma once

#include <stdbool.h>
#include <sys/time.h>


void print_diff_tv(const char *name, struct timeval *end, struct timeval *start,
			bool newline)
{
	printf("%16s: %ld us%c",
		name,
		(end->tv_sec - start->tv_sec) * 1000000
		+ (end->tv_usec - start->tv_usec),
		newline ? '\n' : ' ');
}
