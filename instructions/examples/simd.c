/**
 * Test: SIMD
 *
 * x86: MMX, SSE, AVX
 * arm: NEON(multimedia, signal processing), SVE/SVE2(HPC, machine learning)
 *
 * Better test see ISA-L (https://github.com/intel/isa-l)
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#if defined(CPU_HAVE_NEON)
#include <arm_neon.h>
#endif
#if defined(CPU_HAVE_SVE)
#include <arm_sve.h>
#endif
#if defined(CPU_HAVE_AVX512F) || defined(CPU_HAVE_AVX2)
#include <immintrin.h>
#endif

#define __no_optimize __attribute__((optimize("-O0")))

#define function_attr	__no_optimize

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define DEFINE_CMP_FUNC(funcname, type) \
int funcname(void *x, void *y, size_t n) {	\
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
	return __ret;	\
}

#define prefetch(x) __builtin_prefetch(x)

#define DEFINE_INIT_FUNC(funcname, type)	\
void funcname(void *array, size_t n) {	\
	size_t i;	\
	type *arr = array;	\
	for (i = 0; i < n; i++)	\
		arr[i] = i;	\
	for (i = 0; i < n; i += 64)	\
		prefetch(&arr[i]);	\
}

DEFINE_CMP_FUNC(cmp_arr_u8, uint8_t)
DEFINE_CMP_FUNC(cmp_arr_u16, uint16_t)
DEFINE_CMP_FUNC(cmp_arr_f32, float)
DEFINE_CMP_FUNC(cmp_arr_f64, double)

DEFINE_INIT_FUNC(init_arr_u8, uint8_t)
DEFINE_INIT_FUNC(init_arr_u16, uint16_t)
DEFINE_INIT_FUNC(init_arr_f32, float)
DEFINE_INIT_FUNC(init_arr_f64, double)

typedef void (*test_fn_t)(void *x, void *y, size_t n);
typedef int (*cmp_fn_t)(void *x, void *y, size_t n);
typedef void (*init_fn_t)(void *x, size_t n);

struct test {
	const char *name;
	const char *cpufeature;
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

function_attr
void double_c_X_x_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	double *x = _x;
	double *y = _y;
	for (i = 0; i < n; i++)
		y[i] = x[i] * y[i];
}

function_attr
void double_c_X_add_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	double *x = _x;
	double *y = _y;
	for (i = 0; i < n; i++)
		y[i] = x[i] + y[i];
}

function_attr
void float_c_X_x_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	float *x = _x;
	float *y = _y;
	for (i = 0; i < n; i++)
		y[i] = x[i] * y[i];
}

function_attr
void float_c_X_add_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	float *x = _x;
	float *y = _y;
	for (i = 0; i < n; i++)
		y[i] = x[i] + y[i];
}

function_attr
void u8_c_X_x_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	uint8_t *x = _x;
	uint8_t *y = _y;
	for (i = 0; i < n; i++)
		y[i] = x[i] * y[i];
}

function_attr
void u8_c_X_add_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	uint8_t *x = _x;
	uint8_t *y = _y;
	for (i = 0; i < n; i++)
		y[i] = x[i] + y[i];
}

function_attr
void u16_c_X_x_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	uint16_t *x = _x;
	uint16_t *y = _y;
	for (i = 0; i < n; i++)
		y[i] = x[i] * y[i];
}

#if defined(CPU_HAVE_NEON)
function_attr
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

function_attr
void double_neon_X_add_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	double *x = _x;
	double *y = _y;
	for (i = 0; i < n; i += 2) {
		float64x2_t xi = vld1q_f64(&x[i]);
		float64x2_t yi = vld1q_f64(&y[i]);
		float64x2_t add = vaddq_f64(xi, yi);
		vst1q_f64(&y[i], add);
	}
}

function_attr
void float_neon_X_x_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	float *x = _x;
	float *y = _y;
	for (i = 0; i < n; i += 4) {
		float32x4_t xi = vld1q_f32(&x[i]);
		float32x4_t yi = vld1q_f32(&y[i]);
		float32x4_t sum = vmulq_f32(xi, yi);
		vst1q_f32(&y[i], sum);
	}
}

function_attr
void float_neon_X_add_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	float *x = _x;
	float *y = _y;
	for (i = 0; i < n; i += 4) {
		float32x4_t xi = vld1q_f32(&x[i]);
		float32x4_t yi = vld1q_f32(&y[i]);
		float32x4_t add = vaddq_f32(xi, yi);
		vst1q_f32(&y[i], add);
	}
}

function_attr
void u8_64_neon_X_x_Y(void *_x, void *_y, size_t n)
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

function_attr
void u8_64_neon_X_add_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	uint8_t *x = _x;
	uint8_t *y = _y;
	for (i = 0; i < n; i += 8) {
		uint8x8_t xi = vld1_u8(x + i);
		uint8x8_t yi = vld1_u8(y + i);
		uint8x8_t add = vadd_u8(xi, yi);
		vst1_u8(&y[i], add);
	}
}

function_attr
void u8_128_neon_X_x_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	uint8_t *x = _x;
	uint8_t *y = _y;
	for (i = 0; i < n; i += 16) {
		uint8x16_t xi = vld1q_u8(x + i);
		uint8x16_t yi = vld1q_u8(y + i);
		uint8x16_t mul = vmulq_u8(xi, yi);
		vst1q_u8(&y[i], mul);
	}
}

function_attr
void u8_128_neon_X_add_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	uint8_t *x = _x;
	uint8_t *y = _y;
	for (i = 0; i < n; i += 16) {
		uint8x16_t xi = vld1q_u8(x + i);
		uint8x16_t yi = vld1q_u8(y + i);
		uint8x16_t add = vaddq_u8(xi, yi);
		vst1q_u8(&y[i], add);
	}
}

function_attr
void u16_64_neon_X_x_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	uint16_t *x = _x;
	uint16_t *y = _y;
	for (i = 0; i < n; i += 4) {
		uint16x4_t xi = vld1_u16(x + i);
		uint16x4_t yi = vld1_u16(y + i);
		uint16x4_t mul = vmul_u16(xi, yi);
		vst1_u16(&y[i], mul);
	}
}

function_attr
void u16_128_neon_X_x_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	uint16_t *x = _x;
	uint16_t *y = _y;
	for (i = 0; i < n; i += 8) {
		uint16x8_t xi = vld1q_u16(x + i);
		uint16x8_t yi = vld1q_u16(y + i);
		uint16x8_t mul = vmulq_u16(xi, yi);
		vst1q_u16(&y[i], mul);
	}
}
#endif

#if defined(CPU_HAVE_SVE)
function_attr
void u8_sve_X_x_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	uint8_t *x = _x;
	uint8_t *y = _y;
	size_t vl = svcntb();

	for (i = 0; i < n; i += vl) {
		svbool_t predicate = svwhilelt_b8(i, n);
		svuint8_t xi = svld1_u8(predicate, x + i);
		svuint8_t yi = svld1_u8(predicate, y + i);
		svuint8_t mul = svmul_z(predicate, xi, yi);
		svst1_u8(predicate, y + i, mul);
	}
}

function_attr
void u8_sve_X_add_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	uint8_t *x = _x;
	uint8_t *y = _y;
	size_t vl = svcntb();

	for (i = 0; i < n; i += vl) {
		svbool_t predicate = svwhilelt_b8(i, n);
		svuint8_t xi = svld1_u8(predicate, x + i);
		svuint8_t yi = svld1_u8(predicate, y + i);
		svuint8_t mul = svadd_z(predicate, xi, yi);
		svst1_u8(predicate, y + i, mul);
	}
}

function_attr
void double_sve_X_x_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	double *x = _x;
	double *y = _y;
	size_t vl = svcntb();

	for (i = 0; i < n; i += vl / sizeof(double)) {
		/* or use svptrue_b64(); */
		svbool_t predicate = svwhilelt_b64(i, n);
		svfloat64_t xi = svld1_f64(predicate, x + i);
		svfloat64_t yi = svld1_f64(predicate, y + i);
		svfloat64_t mul = svmul_z(predicate, xi, yi);
		svst1_f64(predicate, y + i, mul);
	}
}

function_attr
void double_sve_X_add_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	double *x = _x;
	double *y = _y;
	size_t vl = svcntb();

	for (i = 0; i < n; i += vl / sizeof(double)) {
		/* or use svptrue_b64(); */
		svbool_t predicate = svwhilelt_b64(i, n);
		svfloat64_t xi = svld1_f64(predicate, x + i);
		svfloat64_t yi = svld1_f64(predicate, y + i);
		svfloat64_t add = svadd_z(predicate, xi, yi);
		svst1_f64(predicate, y + i, add);
	}
}

function_attr
void float_sve_X_x_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	float *x = _x;
	float *y = _y;
	size_t vl = svcntb();

	for (i = 0; i < n; i += vl / sizeof(float)) {
		/* or use svptrue_b64(); */
		svbool_t predicate = svwhilelt_b32(i, n);
		svfloat32_t xi = svld1_f32(predicate, x + i);
		svfloat32_t yi = svld1_f32(predicate, y + i);
		svfloat32_t mul = svmul_z(predicate, xi, yi);
		svst1_f32(predicate, y + i, mul);
	}
}

function_attr
void float_sve_X_add_Y(void *_x, void *_y, size_t n)
{
	size_t i;
	float *x = _x;
	float *y = _y;
	size_t vl = svcntb();

	for (i = 0; i < n; i += vl / sizeof(float)) {
		/* or use svptrue_b64(); */
		svbool_t predicate = svwhilelt_b32(i, n);
		svfloat32_t xi = svld1_f32(predicate, x + i);
		svfloat32_t yi = svld1_f32(predicate, y + i);
		svfloat32_t add = svadd_z(predicate, xi, yi);
		svst1_f32(predicate, y + i, add);
	}
}
#endif

#if defined(CPU_HAVE_AVX2)
function_attr
void double_avx256_X_add_Y(void *_x, void *_y, size_t n)
{
	double *x = _x;
	double *y = _y;
	size_t i, r = n & 3, n2 = n & (-4);
	for(i = -n2; i != 0; i += 4) {
		__m256d yv = _mm256_loadu_pd(&y[i + n2]);
		__m256d xv = _mm256_loadu_pd(&x[i + n2]);
		yv = _mm256_add_pd(xv, yv);
		_mm256_storeu_pd(&y[i + n2], yv);
	}
}

function_attr
void double_avx256_X_mul_Y(void *_x, void *_y, size_t n)
{
	double *x = _x;
	double *y = _y;
	size_t i, r = n & 3, n2 = n & (-4);
	for(i = -n2; i != 0; i += 4) {
		__m256d yv = _mm256_loadu_pd(&y[i + n2]);
		__m256d xv = _mm256_loadu_pd(&x[i + n2]);
		yv = _mm256_mul_pd(xv, yv);
		_mm256_storeu_pd(&y[i + n2], yv);
	}
}
#endif

#if defined(CPU_HAVE_AVX512F)
function_attr
void double_avx512_X_add_Y(void *_x, void *_y, size_t n)
{
	double *x = _x;
	double *y = _y;
	size_t i, r = n & 7, n2 = n & (-8);
	for(i = -n2; i != 0; i += 8) {
		__m512d yv = _mm512_loadu_pd(&y[i + n2]);
		__m512d xv = _mm512_loadu_pd(&x[i + n2]);
		yv = _mm512_add_pd(xv, yv);
		_mm512_storeu_pd(&y[i + n2], yv);
	}
	//__mmask8 mask = _bzhi_u32(-1, r);
	__mmask8 mask = (1 << r) - 1;
	__m512d src;
	__m512d yv = _mm512_mask_loadu_pd(_mm512_undefined_pd(), mask, &y[n2]);
	__m512d xv = _mm512_mask_loadu_pd(_mm512_undefined_pd(), mask, &x[n2]);
	yv = _mm512_mask_add_pd(src, mask, xv, yv);
	_mm512_mask_storeu_pd(&y[n2], mask, yv);
}

function_attr
void double_avx512_X_mul_Y(void *_x, void *_y, size_t n)
{
	double *x = _x;
	double *y = _y;
	size_t i, r = n & 7, n2 = n & (-8);
	for(i = -n2; i != 0; i += 8) {
		__m512d yv = _mm512_loadu_pd(&y[i + n2]);
		__m512d xv = _mm512_loadu_pd(&x[i + n2]);
		yv = _mm512_mul_pd(xv, yv);
		_mm512_storeu_pd(&y[i + n2], yv);
	}
	//__mmask8 mask = _bzhi_u32(-1, r);
	__mmask8 mask = (1 << r) - 1;
	__m512d src;
	__m512d yv = _mm512_mask_loadu_pd(_mm512_undefined_pd(), mask, &y[n2]);
	__m512d xv = _mm512_mask_loadu_pd(_mm512_undefined_pd(), mask, &x[n2]);
	yv = _mm512_mask_mul_pd(src, mask, xv, yv);
	_mm512_mask_storeu_pd(&y[n2], mask, yv);
}
#endif

enum {
	T_BASE_U8_MUL,
	T_BASE_U8_ADD,
	T_BASE_U16,
	T_BASE_F32_MUL,
	T_BASE_F32_ADD,
	T_BASE_F64_MUL,
	T_BASE_F64_ADD,
};

struct test tests[] = {
	[T_BASE_U8_MUL] = {
		.name = "y[i] = x[i] * y[i] (u8)",
		.cpufeature = "C",
		.fn = u8_c_X_x_Y,
		.init = init_arr_u8,
		.cmp = cmp_arr_u8,
		.elem_size = sizeof(uint8_t),
		.spent_us = 0,
		.cmp_with = NULL,
	},
	[T_BASE_U8_ADD] = {
		.name = "y[i] = x[i] + y[i] (u8)",
		.cpufeature = "C",
		.fn = u8_c_X_add_Y,
		.init = init_arr_u8,
		.cmp = cmp_arr_u8,
		.elem_size = sizeof(uint8_t),
		.spent_us = 0,
		.cmp_with = NULL,
	},
	[T_BASE_U16] = {
		.name = "y[i] = x[i] * y[i] (u16)",
		.cpufeature = "C",
		.fn = u16_c_X_x_Y,
		.init = init_arr_u16,
		.cmp = cmp_arr_u16,
		.elem_size = sizeof(uint16_t),
		.spent_us = 0,
		.cmp_with = NULL,
	},
	[T_BASE_F32_MUL] = {
		.name = "y[i] = x[i] * y[i] (f32)",
		.cpufeature = "C",
		.fn = float_c_X_x_Y,
		.init = init_arr_f32,
		.cmp = cmp_arr_f32,
		.elem_size = sizeof(float),
		.spent_us = 0,
		.cmp_with = NULL,
	},
	[T_BASE_F32_ADD] = {
		.name = "y[i] = x[i] + y[i] (f32)",
		.cpufeature = "C",
		.fn = float_c_X_add_Y,
		.init = init_arr_f32,
		.cmp = cmp_arr_f32,
		.elem_size = sizeof(float),
		.spent_us = 0,
		.cmp_with = NULL,
	},
	[T_BASE_F64_MUL] = {
		.name = "y[i] = x[i] * y[i] (f64)",
		.cpufeature = "C",
		.fn = double_c_X_x_Y,
		.init = init_arr_f64,
		.cmp = cmp_arr_f64,
		.elem_size = sizeof(double),
		.spent_us = 0,
		.cmp_with = NULL,
	},
	[T_BASE_F64_ADD] = {
		.name = "y[i] = x[i] + y[i] (f64)",
		.cpufeature = "C",
		.fn = double_c_X_add_Y,
		.init = init_arr_f64,
		.cmp = cmp_arr_f64,
		.elem_size = sizeof(double),
		.spent_us = 0,
		.cmp_with = NULL,
	},
#if defined(CPU_HAVE_NEON)
	{
		.name = "y[i] = x[i] * y[i] (u8) lane=128",
		.cpufeature = "neon",
		.fn = u8_128_neon_X_x_Y,
		.init = init_arr_u8,
		.cmp = cmp_arr_u8,
		.elem_size = sizeof(uint8_t),
		.spent_us = 0,
		.cmp_with = &tests[T_BASE_U8_MUL],
	},
	{
		.name = "y[i] = x[i] + y[i] (u8) lane=128",
		.cpufeature = "neon",
		.fn = u8_128_neon_X_add_Y,
		.init = init_arr_u8,
		.cmp = cmp_arr_u8,
		.elem_size = sizeof(uint8_t),
		.spent_us = 0,
		.cmp_with = &tests[T_BASE_U8_ADD],
	},
	{
		.name = "y[i] = x[i] * y[i] (u8) lane=64",
		.cpufeature = "neon",
		.fn = u8_64_neon_X_x_Y,
		.init = init_arr_u8,
		.cmp = cmp_arr_u8,
		.elem_size = sizeof(uint8_t),
		.spent_us = 0,
		.cmp_with = &tests[T_BASE_U8_MUL],
	},
	{
		.name = "y[i] = x[i] + y[i] (u8) lane=64",
		.cpufeature = "neon",
		.fn = u8_64_neon_X_add_Y,
		.init = init_arr_u8,
		.cmp = cmp_arr_u8,
		.elem_size = sizeof(uint8_t),
		.spent_us = 0,
		.cmp_with = &tests[T_BASE_U8_ADD],
	},
	{
		.name = "y[i] = x[i] * y[i] (u16) lane=128",
		.cpufeature = "neon",
		.fn = u16_128_neon_X_x_Y,
		.init = init_arr_u16,
		.cmp = cmp_arr_u16,
		.elem_size = sizeof(uint16_t),
		.spent_us = 0,
		.cmp_with = &tests[T_BASE_U16],
	},
	{
		.name = "y[i] = x[i] * y[i] (u16) lane=64",
		.cpufeature = "neon",
		.fn = u16_64_neon_X_x_Y,
		.init = init_arr_u16,
		.cmp = cmp_arr_u16,
		.elem_size = sizeof(uint16_t),
		.spent_us = 0,
		.cmp_with = &tests[T_BASE_U16],
	},
	{
		.name = "y[i] = x[i] * y[i] (f32)",
		.cpufeature = "neon",
		.fn = float_neon_X_x_Y,
		.init = init_arr_f32,
		.cmp = cmp_arr_f32,
		.elem_size = sizeof(float),
		.spent_us = 0,
		.cmp_with = &tests[T_BASE_F32_MUL],
	},
	{
		.name = "y[i] = x[i] + y[i] (f32)",
		.cpufeature = "neon",
		.fn = float_neon_X_add_Y,
		.init = init_arr_f32,
		.cmp = cmp_arr_f32,
		.elem_size = sizeof(float),
		.spent_us = 0,
		.cmp_with = &tests[T_BASE_F32_ADD],
	},
	{
		.name = "y[i] = x[i] * y[i] (f64)",
		.cpufeature = "neon",
		.fn = double_neon_X_x_Y,
		.init = init_arr_f64,
		.cmp = cmp_arr_f64,
		.elem_size = sizeof(double),
		.spent_us = 0,
		.cmp_with = &tests[T_BASE_F64_MUL],
	},
	{
		.name = "y[i] = x[i] + y[i] (f64)",
		.cpufeature = "neon",
		.fn = double_neon_X_add_Y,
		.init = init_arr_f64,
		.cmp = cmp_arr_f64,
		.elem_size = sizeof(double),
		.spent_us = 0,
		.cmp_with = &tests[T_BASE_F64_ADD],
	},
#endif
#if defined(CPU_HAVE_SVE)
	{
		.name = "y[i] = x[i] * y[i] (u8)",
		.cpufeature = "sve",
		.fn = u8_sve_X_x_Y,
		.init = init_arr_u8,
		.cmp = cmp_arr_u8,
		.elem_size = sizeof(uint8_t),
		.spent_us = 0,
		.cmp_with = &tests[T_BASE_U8_MUL],
	},
	{
		.name = "y[i] = x[i] + y[i] (u8)",
		.cpufeature = "sve",
		.fn = u8_sve_X_add_Y,
		.init = init_arr_u8,
		.cmp = cmp_arr_u8,
		.elem_size = sizeof(uint8_t),
		.spent_us = 0,
		.cmp_with = &tests[T_BASE_U8_ADD],
	},
	{
		.name = "y[i] = x[i] * y[i] (f32)",
		.cpufeature = "sve",
		.fn = float_sve_X_x_Y,
		.init = init_arr_f32,
		.cmp = cmp_arr_f32,
		.elem_size = sizeof(float),
		.spent_us = 0,
		.cmp_with = &tests[T_BASE_F32_MUL],
	},
	{
		.name = "y[i] = x[i] + y[i] (f32)",
		.cpufeature = "sve",
		.fn = float_sve_X_add_Y,
		.init = init_arr_f32,
		.cmp = cmp_arr_f32,
		.elem_size = sizeof(float),
		.spent_us = 0,
		.cmp_with = &tests[T_BASE_F32_ADD],
	},
	{
		.name = "y[i] = x[i] * y[i] (f64)",
		.cpufeature = "sve",
		.fn = double_sve_X_x_Y,
		.init = init_arr_f64,
		.cmp = cmp_arr_f64,
		.elem_size = sizeof(double),
		.spent_us = 0,
		.cmp_with = &tests[T_BASE_F64_MUL],
	},
	{
		.name = "y[i] = x[i] + y[i] (f64)",
		.cpufeature = "sve",
		.fn = double_sve_X_add_Y,
		.init = init_arr_f64,
		.cmp = cmp_arr_f64,
		.elem_size = sizeof(double),
		.spent_us = 0,
		.cmp_with = &tests[T_BASE_F64_ADD],
	},
#endif
#if defined(CPU_HAVE_AVX2)
	{
		.name = "y[i] = x[i] * y[i] (f64)",
		.cpufeature = "avx2",
		.fn = double_avx256_X_mul_Y,
		.init = init_arr_f64,
		.cmp = cmp_arr_f64,
		.elem_size = sizeof(double),
		.spent_us = 0,
		.cmp_with = &tests[T_BASE_F64_MUL],
	},
	{
		.name = "y[i] = x[i] + y[i] (f64)",
		.cpufeature = "avx2",
		.fn = double_avx256_X_add_Y,
		.init = init_arr_f64,
		.cmp = cmp_arr_f64,
		.elem_size = sizeof(double),
		.spent_us = 0,
		.cmp_with = &tests[T_BASE_F64_ADD],
	},
#endif
#if defined(CPU_HAVE_AVX512F)
	{
		.name = "y[i] = x[i] * y[i] (f64)",
		.cpufeature = "avx512f",
		.fn = double_avx512_X_mul_Y,
		.init = init_arr_f64,
		.cmp = cmp_arr_f64,
		.elem_size = sizeof(double),
		.spent_us = 0,
		.cmp_with = &tests[T_BASE_F64_MUL],
	},
	{
		.name = "y[i] = x[i] + y[i] (f64)",
		.cpufeature = "avx512f",
		.fn = double_avx512_X_add_Y,
		.init = init_arr_f64,
		.cmp = cmp_arr_f64,
		.elem_size = sizeof(double),
		.spent_us = 0,
		.cmp_with = &tests[T_BASE_F64_ADD],
	},
#endif
};

int main(int argc, char *argv[])
{
	int i, j;
	size_t n = 8192;
	size_t nloop = 10000;

	fprintf(stderr, "USAGE: %s [NLOOP, default %ld]\n", argv[0], nloop);

	if (argc > 1) {
		nloop = strtol(argv[1], NULL, 10);
		if (!nloop) {
			fprintf(stderr, "ERROR: invalid argument %s\n", argv[1]);
			exit(EXIT_FAILURE);
		}
	}

	fprintf(stderr, "Test nloop = %ld\n", nloop);
#if defined(CPU_HAVE_SVE)
	uint64_t lanes = svcntb();
	printf("SVE vector width is %d bytes (%d bits).\n", lanes, lanes * 8);
#endif

	for (j = 0; j < nloop; j++) {
#ifdef DEBUG
		if (j % 1000 == 0)
			printf("Testing %d/%d\n", j, nloop);
#endif
		if (j % 1000 == 0)
			fprintf(stderr, ".");

		for (i = 0; i < ARRAY_SIZE(tests); i++) {
			unsigned long start;
			struct test *t = &tests[i];
			struct test *t_cmp = t->cmp_with;

#ifdef DEBUG
			printf("Testing %s\n", t->name);
#endif

			t->x = malloc(t->elem_size * n);
			t->y = malloc(t->elem_size * n);

			t->init(t->x, n);
			t->init(t->y, n);

			start = usecs();
			t->fn(t->x, t->y, n);
			t->spent_us += usecs() - start;

			if (t_cmp)
				t->cmp_rslt += t->cmp(t_cmp->y, t->y, n);
			else
				t->cmp_rslt += 0;
		}
	}
	fprintf(stderr, "\n");

	printf("Length of array %ld\n", n);
	printf("%-50s %-16s %-16s %-16s %-8s\n", "TEST_NAME", "FLAGS",
		"SPENT(us)", "SPENT(ms)", "RSLT");

	for (i = 0; i < ARRAY_SIZE(tests); i++) {
		struct test *t = &tests[i];
		printf("%-50s %-16s %-16ld %-16ld %-8s\n", t->name,
			t->cpufeature, t->spent_us, t->spent_us / 1000,
			t->cmp_rslt ? "\033[31mFailed\033[m" : "\033[32mPassed\033[m");
	}

	for (i = 0; i < ARRAY_SIZE(tests); i++) {
		struct test *t = &tests[i];
		free(t->x);
		free(t->y);
	}
	return 0;
}
