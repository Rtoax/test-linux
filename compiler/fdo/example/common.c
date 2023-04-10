#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "common.h"


void
swap_int(int *a, int *b)
{
	int t;

	t = *a;
	*a = *b;
	*b = t;
}

void
set_rand_value(int *arr)
{
	*arr = rand();
}

void
rand_array(int *arr, int arr_len)
{
	int i;

	for (i = 0; i < arr_len; ++i) {
		set_rand_value(&arr[i]);
	}
}

static struct timeval tm1;

void
start(void)
{
	gettimeofday(&tm1, NULL);
}

void
stop(void)
{
	struct timeval tm2;
	gettimeofday(&tm2, NULL);

	unsigned long long t = 1000000 * (tm2.tv_sec - tm1.tv_sec) +
							(tm2.tv_usec - tm1.tv_usec);

	printf("%llu us\n", t);
}
