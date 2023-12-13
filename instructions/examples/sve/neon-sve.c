#include <stdio.h>
#include <malloc.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

typedef void (*test_fn_t)(double *x, double *y, double a, size_t n);

struct test {
	const char *name;
	test_fn_t fn;
	unsigned long spent_us;
	double *x, *y;
};


static inline unsigned long usecs(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000UL + tv.tv_usec;
}

void daxpy_c(double *x, double *y, double a, size_t n)
{
	size_t i;
	for (i = 0; i < n; i++)
		y[i] = a * x[i] + y[i];
}

void daxpy_neon(double *x, double *y, double a, size_t n)
{
}

void init_arr(double *arr, size_t n)
{
	size_t i;
	for (i = 0; i < n; i++)
		arr[i] = i;
}

struct test tests[] = {
	{ "C", daxpy_c, 0, },
	{ "Neon", daxpy_neon, 0, },
};

int main(int argc, char *argv[])
{
	int i;
	size_t n = 100000000;
	double a = 1.1;


	for (i = 0; i < ARRAY_SIZE(tests); i++) {
		unsigned long start;
		struct test *t = &tests[i];

		t->x = malloc(sizeof(double) * n);
		t->y = malloc(sizeof(double) * n);

		init_arr(t->x, n);
		init_arr(t->y, n);

		start = usecs();
		t->fn(t->x, t->y, a, n);
		t->spent_us = usecs() - start;
	}

	for (i = 0; i < ARRAY_SIZE(tests); i++) {
		struct test *t = &tests[i];
		free(t->x);
		free(t->y);
	}

	return 0;
}
