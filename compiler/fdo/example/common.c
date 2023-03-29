#include <stdio.h>
#include <sys/time.h>
#include "common.h"


void __cacheline_align __noinline
FN(swap_int)(int *a, int *b)
{
	int t;
	char pad[__cacheline_size];

	t = *a;
	*a = *b;
	*b = t;
}

static struct timeval tm1;

void __cacheline_align __noinline
FN(start)(void)
{
	gettimeofday(&tm1, NULL);
}

void __cacheline_align __noinline
FN(stop)(void)
{
	struct timeval tm2;
	gettimeofday(&tm2, NULL);

	unsigned long long t = 1000000 * (tm2.tv_sec - tm1.tv_sec) +
							(tm2.tv_usec - tm1.tv_usec);

	printf("%llu us\n", t);
}
