#include <stdio.h>
#include <malloc.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <arm_neon.h>
#if !defined(CONFIG_NO_SVE)
#include <arm_sve.h>
#endif

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

typedef void (*test_u8_fn_t)(uint8_t *x, uint8_t *y, uint8_t a, size_t n);
typedef void (*test_fn_t)(double *x, double *y, double a, size_t n);

struct test {
	const char *name;
	union {
		test_u8_fn_t fn_u8;
		test_fn_t fn_double;
	};
	unsigned long spent_us;
	void *x, *y;
	int cmp;
};


static inline unsigned long usecs(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000UL + tv.tv_usec;
}

void double_c_X_x_Y(double *x, double *y, double a, size_t n)
{
	size_t i;
	for (i = 0; i < n; i++)
		y[i] = x[i] * y[i];
}

void u8_c_X_x_Y(uint8_t *x, uint8_t *y, uint8_t a, size_t n)
{
	size_t i;
	for (i = 0; i < n; i++)
		y[i] = x[i] * y[i];
}

void double_neon_X_x_Y(double *x, double *y, double a, size_t n)
{
	size_t i;
	for (i = 0; i < n; i += 2) {
		float64x2_t xi = vld1q_f64(&x[i]);
		float64x2_t yi = vld1q_f64(&y[i]);
		float64x2_t sum = vmulq_f64(xi, yi);
		vst1q_f64(&y[i], sum);
	}
}

void u8_neon_X_x_Y(uint8_t *x, uint8_t *y, uint8_t a, size_t n)
{
	size_t i;
	for (i = 0; i < n; i += 8) {
		uint8x8_t xi = vld1_u8(x + i);
		uint8x8_t yi = vld1_u8(y + i);
		uint8x8_t mul = vmul_u8(xi, yi);
		vst1_u8(&y[i], mul);
	}
}

#if !defined(CONFIG_NO_SVE)
void u8_sve_X_x_Y(uint8_t *x, uint8_t *y, uint8_t a, size_t n)
{
	size_t i;
	size_t vl = svcntb();
	printf("SVE lane %ld\n", vl);

	for (i = 0; i < n; i += vl) {
		svbool_t predicate = svwhilelt_b8(i, n);
		svuint8_t xi = svld1_u8(predicate, x + i);
		svuint8_t yi = svld1_u8(predicate, y + i);
		svuint8_t mul = svmul_z(predicate, xi, yi);
		svst1_u8(predicate, y + i, mul);
	}
}

void double_sve_X_x_Y(double *x, double *y, double a, size_t n)
{
	size_t i;
	size_t vl = svcntb();
	printf("SVE lane %ld\n", vl);

	for (i = 0; i < n; i += vl / sizeof(double)) {
		/* or use svptrue_b64(); */
		svbool_t predicate = svwhilelt_b64(i, n);
		svfloat64_t xi = svld1_f64(predicate, x + i);
		svfloat64_t yi = svld1_f64(predicate, y + i);
		svfloat64_t mul = svmul_z(predicate, xi, yi);
		svst1_f64(predicate, y + i, mul);
	}
}
#endif

#define init_arr(type, array, n) do {	\
	size_t i;	\
	type *arr = array;	\
	for (i = 0; i < n; i++)	\
		arr[i] = i;	\
} while (0)

#define cmp_arr(type, x, y, n) ({	\
	int __ret = 0;	\
	size_t ___i;	\
	type *___x = x;	\
	type *___y = y;	\
	for (___i = 0; ___i < n; ___i++)	\
		if (___x[___i] != ___y[___i]) {	\
			fprintf(stderr, "F:%ld\n", ___i);	\
			__ret = 1;	\
			break;	\
		}	\
	__ret;	\
})

struct test tests_u8[] = {
	{
		.name = "   C: y[i] = x[i] * y[i] (u8)",
		.fn_u8 = u8_c_X_x_Y,
		.spent_us = 0,
	},
	{
		.name = "Neon: y[i] = x[i] * y[i] (u8)",
		.fn_u8 = u8_neon_X_x_Y,
		.spent_us = 0,
	},
#if !defined(CONFIG_NO_SVE)
	{
		.name = " Sve: y[i] = x[i] * y[i] (u8)",
		.fn_u8 = u8_sve_X_x_Y,
		.spent_us = 0,
	},
#endif
};

struct test tests_double[] = {
	{
		.name = "   C: y[i] = x[i] * y[i] (f64)",
		.fn_double = double_c_X_x_Y,
		.spent_us = 0,
	},
	{
		.name = "Neon: y[i] = x[i] * y[i] (f64)",
		.fn_double = double_neon_X_x_Y,
		.spent_us = 0,
	},
#if !defined(CONFIG_NO_SVE)
	{
		.name = " Sve: y[i] = x[i] * y[i] (f64)",
		.fn_double = double_sve_X_x_Y,
		.spent_us = 0,
	},
#endif
};

int main(int argc, char *argv[])
{
	int i;
	size_t n = 10000000;
	double a = 1.1;

	struct test *t_double_base = &tests_double[0];
	struct test *t_u8_base = &tests_u8[0];

	for (i = 0; i < ARRAY_SIZE(tests_double); i++) {
		unsigned long start;
		struct test *t = &tests_double[i];

		printf("Testing %s\n", t->name);

		t->x = malloc(sizeof(double) * n);
		t->y = malloc(sizeof(double) * n);

		init_arr(double, t->x, n);
		init_arr(double, t->y, n);

		start = usecs();
		t->fn_double(t->x, t->y, a, n);
		t->spent_us = usecs() - start;

		if (i != 0)
			t->cmp = cmp_arr(double, t_double_base->y, t->y, n);
		else
			t->cmp = 0;
	}
	for (i = 0; i < ARRAY_SIZE(tests_u8); i++) {
		unsigned long start;
		struct test *t = &tests_u8[i];

		printf("Testing %s\n", t->name);

		t->x = malloc(sizeof(uint8_t) * n);
		t->y = malloc(sizeof(uint8_t) * n);

		init_arr(uint8_t, t->x, n);
		init_arr(uint8_t, t->y, n);

		start = usecs();
		t->fn_u8(t->x, t->y, a, n);
		t->spent_us = usecs() - start;

		if (i != 0)
			t->cmp = cmp_arr(uint8_t, t_u8_base->y, t->y, n);
		else
			t->cmp = 0;
	}


	printf("Length of array %ld\n", n);
	printf("%-50s %-16s %-8s\n", "TEST_NAME", "SPENT(us)", "RSLT");

	for (i = 0; i < ARRAY_SIZE(tests_double); i++) {
		struct test *t = &tests_double[i];
		printf("%-50s %-16ld %-8s\n", t->name, t->spent_us, t->cmp ? "Failed" : "Passed");
	}
	for (i = 0; i < ARRAY_SIZE(tests_u8); i++) {
		struct test *t = &tests_u8[i];
		printf("%-50s %-16ld %-8s\n", t->name, t->spent_us, t->cmp ? "Failed" : "Passed");
	}

	for (i = 0; i < ARRAY_SIZE(tests_double); i++) {
		struct test *t = &tests_double[i];
		free(t->x);
		free(t->y);
	}
	for (i = 0; i < ARRAY_SIZE(tests_u8); i++) {
		struct test *t = &tests_u8[i];
		free(t->x);
		free(t->y);
	}
	return 0;
}
