#pragma once

#include <stdbool.h>
#include <sys/time.h>

#define barrier() asm volatile ("" : : : "memory")
#define mb() asm volatile ("mfence" : : : "memory")
#define __cacheline_aligned__ __attribute__((aligned(128)))
#define ACCESS_ONCE(x) (*(volatile typeof(x)*)&x)
#define __always_inline__ __attribute__((always_inline))


void print_diff_tv(const char *name, struct timeval *end, struct timeval *start,
			bool newline)
{
	printf("%16s: %ld us%c",
		name,
		(end->tv_sec - start->tv_sec) * 1000000
		+ (end->tv_usec - start->tv_usec),
		newline ? '\n' : ' ');
}
