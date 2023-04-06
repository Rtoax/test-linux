#include <stdio.h>
#include <sys/time.h>
#include "common.h"


void
FN(swap_int)(int *a, int *b)
{
	int t;

	t = *a;
	*a = *b;
	*b = t;
}

void
FN(set_rand_value)(int *arr)
{
	*arr = rand();
}

DEFINE_FN_PAD(p1);
DEFINE_FN_PAD(p2);
DEFINE_FN_PAD(p3);
DEFINE_FN_PAD(p4);
DEFINE_FN_PAD(p5);
DEFINE_FN_PAD(p6);
DEFINE_FN_PAD(p7);
DEFINE_FN_PAD(p8);
DEFINE_FN_PAD(p9);
DEFINE_FN_PAD(p10);
DEFINE_FN_PAD(p11);

void
FN(rand_array)(int *arr, int arr_len)
{
	int i;

	for (i = 0; i < arr_len; ++i) {
		CALL(set_rand_value)(&arr[i]);
	}
}

static struct timeval tm1;

void
FN(start)(void)
{
	gettimeofday(&tm1, NULL);
}

void
FN(stop)(void)
{
	struct timeval tm2;
	gettimeofday(&tm2, NULL);

	unsigned long long t = 1000000 * (tm2.tv_sec - tm1.tv_sec) +
							(tm2.tv_usec - tm1.tv_usec);

	printf("%llu us\n", t);
}
