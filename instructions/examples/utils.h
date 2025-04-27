#pragma once

#include <sched.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>

#define barrier() asm volatile ("" : : : "memory")
#define mb() asm volatile ("mfence" : : : "memory")
#define __cacheline_aligned__ __attribute__((aligned(128)))
#define ACCESS_ONCE(x) (*(volatile typeof(x)*)&x)
#define __always_inline__ __attribute__((always_inline))

#define ARRAY_SIZE(arr)	(sizeof(arr)/sizeof(arr[0]))


uint64_t diff_tv_usec(struct timeval *end, struct timeval *start)
{
	return (end->tv_sec - start->tv_sec) * 1000000ULL
		+ (end->tv_usec - start->tv_usec);
}

void print_diff_tv(const char *name, struct timeval *end, struct timeval *start,
			bool newline)
{
	printf("%16s: %ld us%c",
		name, diff_tv_usec(end, start),
		newline ? '\n' : ' ');
}

