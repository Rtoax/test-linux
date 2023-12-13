#include <stdio.h>
#include <malloc.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <arm_neon.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

typedef void (*test_fn_t)(double *x, double *y, double a, size_t n);

struct test {
	const char *name;
	test_fn_t fn;
	unsigned long spent_us;
	double *x, *y;
	int cmp;
};


static inline unsigned long usecs(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000UL + tv.tv_usec;
}

void c_X_x_Y(double *x, double *y, double a, size_t n)
{
	size_t i;
	for (i = 0; i < n; i++)
		y[i] = x[i] * y[i];
}

void neon_X_x_Y(double *x, double *y, double a, size_t n)
{
	size_t i;
	for (i = 0; i < n; i += 2) {
		float64x2_t xi = vld1q_f64(&x[i]);
		float64x2_t yi = vld1q_f64(&y[i]);
		float64x2_t sum = vmulq_f64(xi, yi);
		vst1q_f64(&y[i], sum);
	}
}

void init_arr(double *arr, size_t n)
{
	size_t i;
	for (i = 0; i < n; i++)
		arr[i] = i;
}

int cmp_arr(double *x, double *y, size_t n)
{
	size_t i;
	for (i = 0; i < n; i++)
		if (x[i] != y[i])
			return 1;
	return 0;
}

struct test tests[] = {
	{
		.name = "   C: y[i] = x[i] * y[i]",
		.fn = c_X_x_Y,
		.spent_us = 0,
	},
	{
		.name = "Neon: y[i] = x[i] * y[i]",
		.fn = neon_X_x_Y,
		.spent_us = 0,
	},
};

int main(int argc, char *argv[])
{
	int i;
	size_t n = 10000000;
	double a = 1.1;

	struct test *t_base = &tests[0];

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

		if (i != 0)
			t->cmp = cmp_arr(t_base->y, t->y, n);
		else
			t->cmp = 0;
	}

	printf("Length of array %ld\n", n);
	printf("%-32s %-16s %-8s\n", "TEST_NAME", "SPENT(us)", "RSLT");

	for (i = 0; i < ARRAY_SIZE(tests); i++) {
		struct test *t = &tests[i];
		printf("%-32s %-16ld %-8s\n", t->name, t->spent_us, t->cmp ? "Failed" : "Passed");
	}

	for (i = 0; i < ARRAY_SIZE(tests); i++) {
		struct test *t = &tests[i];
		free(t->x);
		free(t->y);
	}
	return 0;
}
