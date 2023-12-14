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

#define DEFINE_CMP_FUNC(funcname, type) \
int funcname(void *x, void *y, size_t n) {	\
	int __ret = 0;	\
	size_t ___i;	\
	type *___x = x;	\
	type *___y = y;	\
	printf("call %s\n", #funcname);	\
	for (___i = 0; ___i < n; ___i++)	\
		if (___x[___i] != ___y[___i]) {	\
			fprintf(stderr, "F:%ld\n", ___i);	\
			__ret = 1;	\
			break;	\
		}	\
	return __ret;	\
}

#define DEFINE_INIT_FUNC(funcname, type)	\
void funcname(void *array, size_t n) {	\
	size_t i;	\
	type *arr = array;	\
	printf("call %s\n", #funcname);	\
	for (i = 0; i < n; i++)	\
		arr[i] = i;	\
}

DEFINE_CMP_FUNC(cmp_arr_u8, uint8_t)
DEFINE_CMP_FUNC(cmp_arr_f64, double)

DEFINE_INIT_FUNC(init_arr_u8, uint8_t)
DEFINE_INIT_FUNC(init_arr_f64, double)

typedef void (*test_fn_t)(void *x, void *y, size_t n);
typedef int (*cmp_fn_t)(void *x, void *y, size_t n);
typedef void (*init_fn_t)(void *x, size_t n);

struct test {
	const char *name;
	test_fn_t fn;
	cmp_fn_t cmp;
	init_fn_t init;
	ssize_t elem_size;
	unsigned long spent_us;
	void *x, *y;
	struct test *cmp_with;
	int cmp_rslt;
};


static inline unsigned long usecs(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000UL + tv.tv_usec;
}

void double_c_X_x_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	double *x = _x;
	double *y = _y;
	for (i = 0; i < n; i++)
		y[i] = x[i] * y[i];
}

void u8_c_X_x_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	uint8_t *x = _x;
	uint8_t *y = _y;
	for (i = 0; i < n; i++)
		y[i] = x[i] * y[i];
}

void double_neon_X_x_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	double *x = _x;
	double *y = _y;
	for (i = 0; i < n; i += 2) {
		float64x2_t xi = vld1q_f64(&x[i]);
		float64x2_t yi = vld1q_f64(&y[i]);
		float64x2_t sum = vmulq_f64(xi, yi);
		vst1q_f64(&y[i], sum);
	}
}

void u8_neon_X_x_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	uint8_t *x = _x;
	uint8_t *y = _y;
	for (i = 0; i < n; i += 8) {
		uint8x8_t xi = vld1_u8(x + i);
		uint8x8_t yi = vld1_u8(y + i);
		uint8x8_t mul = vmul_u8(xi, yi);
		vst1_u8(&y[i], mul);
	}
}

#if !defined(CONFIG_NO_SVE)
void u8_sve_X_x_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	uint8_t *x = _x;
	uint8_t *y = _y;
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

void double_sve_X_x_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	double *x = _x;
	double *y = _y;
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

struct test tests[] = {
	[0] = {
		.name = "   C: y[i] = x[i] * y[i] (u8)",
		.fn = u8_c_X_x_Y,
		.init = init_arr_u8,
		.cmp = cmp_arr_u8,
		.elem_size = sizeof(uint8_t),
		.spent_us = 0,
		.cmp_with = NULL,
	},
	[1] = {
		.name = "   C: y[i] = x[i] * y[i] (f64)",
		.fn = double_c_X_x_Y,
		.init = init_arr_f64,
		.cmp = cmp_arr_f64,
		.elem_size = sizeof(double),
		.spent_us = 0,
		.cmp_with = NULL,
	},
	{
		.name = "Neon: y[i] = x[i] * y[i] (u8)",
		.fn = u8_neon_X_x_Y,
		.init = init_arr_u8,
		.cmp = cmp_arr_u8,
		.elem_size = sizeof(uint8_t),
		.spent_us = 0,
		.cmp_with = &tests[0],
	},
	{
		.name = "Neon: y[i] = x[i] * y[i] (f64)",
		.fn = double_neon_X_x_Y,
		.init = init_arr_f64,
		.cmp = cmp_arr_f64,
		.elem_size = sizeof(double),
		.spent_us = 0,
		.cmp_with = &tests[1],
	},
#if !defined(CONFIG_NO_SVE)
	{
		.name = " Sve: y[i] = x[i] * y[i] (u8)",
		.fn = u8_sve_X_x_Y,
		.init = init_arr_u8,
		.cmp = cmp_arr_u8,
		.elem_size = sizeof(uint8_t),
		.spent_us = 0,
		.cmp_with = &tests[0],
	},
	{
		.name = " Sve: y[i] = x[i] * y[i] (f64)",
		.fn = double_sve_X_x_Y,
		.init = init_arr_f64,
		.cmp = cmp_arr_f64,
		.elem_size = sizeof(double),
		.spent_us = 0,
		.cmp_with = &tests[1],
	},
#endif
};

int main(int argc, char *argv[])
{
	int i;
	size_t n = 10000000;

	for (i = 0; i < ARRAY_SIZE(tests); i++) {
		unsigned long start;
		struct test *t = &tests[i];
		struct test *t_cmp = t->cmp_with;

		printf("Testing %s\n", t->name);

		t->x = malloc(t->elem_size * n);
		t->y = malloc(t->elem_size * n);

		t->init(t->x, n);
		t->init(t->y, n);

		start = usecs();
		t->fn(t->x, t->y, n);
		t->spent_us = usecs() - start;

		if (t_cmp)
			t->cmp_rslt = t->cmp(t_cmp->y, t->y, n);
		else
			t->cmp_rslt = 0;
	}

	printf("Length of array %ld\n", n);
	printf("%-50s %-16s %-8s\n", "TEST_NAME", "SPENT(us)", "RSLT");

	for (i = 0; i < ARRAY_SIZE(tests); i++) {
		struct test *t = &tests[i];
		printf("%-50s %-16ld %-8s\n", t->name, t->spent_us, t->cmp_rslt ? "Failed" : "Passed");
	}

	for (i = 0; i < ARRAY_SIZE(tests); i++) {
		struct test *t = &tests[i];
		free(t->x);
		free(t->y);
	}
	return 0;
}
