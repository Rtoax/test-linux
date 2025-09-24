// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * Test various floating point precisions on various hardware such as CPU and
 * GPU. Different hardware handles precision and overflow differently.
 *
 * IEEE 754 floating-point formats:
 *
 *   16-bit: Half (binary16)
 *   32-bit: Single (binary32), decimal32
 *   64-bit: Double (binary64), decimal64
 *   128-bit: Quadruple (binary128), decimal128
 *   256-bit: Octuple (binary256)
 *   Extended precision
 *  Other:
 *   Minifloat
 *   bfloat16
 *   TensorFloat-32
 *   Microsoft Binary Format
 *   IBM hexadecimal floating-point
 *   PMBus Linear-11
 *   G.711 8-bit floats
 *   Alternatives
 *   Arbitrary precision
 *   Block floating point
 *   Tapered floating point
 *   Posit
 *
 * Overflow:
 *
 * The IEEE 754 standard specifies that the hardware should perform the
 * following when an overflow occurs:
 *
 *   Positive overflow: If the result is a positive number that is too large,
 *   it is converted to positive infinity (+Inf).
 *
 *   Negative overflow: If the result is a negative number that is too large
 *   in magnitude, it is converted to negative infinity (-Inf).
 *
 * Macros:
 *
 * - SUPPORT__Float16: compiler support _Float16;
 * - SUPPORT_FP16: support _Float16 or cuda's half;
 *
 * Refs:
 * - https://en.wikipedia.org/wiki/IEEE_754-2008_revision
 * - https://en.wikipedia.org/wiki/Half-precision_floating-point_format
 * - https://en.wikipedia.org/wiki/Single-precision_floating-point_format
 * - https://en.wikipedia.org/wiki/Double-precision_floating-point_format
 * - https://github.com/Maratyszcza/FP16
 */
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <byteswap.h>
#include <float.h>
#include <string.h>

#if defined(__HPCC__) || defined(__NVCC__)
# define HAVE_CUDA	1
# if defined(__HPCC__)	/* MetaX */
#  include <hccl.h>
#  include <hpcc_fp16.h>
#  include <hc_runtime.h>
#  include "cuda_adapter.h"
#  ifndef SUPPORT__Float16
#   define SUPPORT__Float16 /* HPCC always support _Float16 */
#  endif
# elif defined(__NVCC__)	/* Nvidia */
#  include <cuda_fp16.h>
#  include <cuda_runtime.h>
#  include "cuda_helpers.h"
#  ifdef SUPPORT__Float16
#   undef SUPPORT__Float16
#   warning Error: Internal Compiler Error (codegen): "unsupported float variant!"
#  endif
# endif
# define DIM	<<<1, 1>>>
# define __mydevice__	__device__
# define __myglobal__	__global__
# define __myconst__	__constant__
# define mysync()	cudaDeviceSynchronize()
#else
# define DIM
# define __mydevice__
# define __myglobal__
# define __myconst__	const
# define mysync()
#endif

/**
 * Note: Use _Float16 first
 */
#ifdef SUPPORT__Float16
# define SUPPORT_FP16
# define compat_fp16	_Float16
# define compat_half2float(v)	((float)v)
# define compat_float2half(v)	((_Float16)v)
#elif defined(HAVE_CUDA)
# define SUPPORT_FP16
# define compat_fp16	half
# define compat_half2float(v)	__half2float(v)
# define compat_float2half(v)	__float2half(v)
#endif

#ifndef offsetof
# define offsetof(TYPE, MEMBER)    ((size_t)&((TYPE *)0)->MEMBER)
#endif

#define ARRAY_SIZE(arr)	(sizeof(arr) / sizeof(arr[0]))
const static char *ansi[] = {
	"\033[32m",
	"\033[33m",
	"\033[34m",
	"\033[35m",
	"\033[36m",
};
static const char *reset = "\033[m";
static unsigned long ansi_idx = 0;

#define seperator() do {	\
		printf("%s%s", reset, ansi[ansi_idx++ % ARRAY_SIZE(ansi)]);	\
	} while (0)
#define reset() do {	\
		printf("%s", reset);	\
		ansi_idx++;	\
	} while (0)


typedef union fp64 {
	struct {
		#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		uint64_t fraction:52;
		uint64_t exponent:11;
		uint64_t sign:1;
		# define __FP64_INITIALIZER(s, e, f) {f, e, s}
		#else
		uint64_t sign:1;
		uint64_t exponent:11;
		uint64_t fraction:52;
		# define __FP64_INITIALIZER(s, e, f) {s, e, f}
		#endif
	} __attribute__((packed));
	double f64;
	uint64_t i64;
#define FP64_INITIALIZER(s, e, f) {__FP64_INITIALIZER(s, e, f)}
#define FP64(s, e, f) (((s & 0x1UL) << 63) | ((e & 0x7ffUL) << 52) | \
		       ((f & 0xfffffffffffffUL)))
} fp64_t;

typedef union fp32 {
	struct {
		#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		uint32_t fraction:23;
		uint32_t exponent:8;
		uint32_t sign:1;
		# define __FP32_INITIALIZER(s, e, f) {f, e, s}
		#else
		uint32_t sign:1;
		uint32_t exponent:8;
		uint32_t fraction:23;
		# define __FP32_INITIALIZER(s, e, f) {s, e, f}
		#endif
	} __attribute__((packed));
	float f32;
	uint32_t i32;
#define FP32_INITIALIZER(s, e, f) {__FP32_INITIALIZER(s, e, f)}
} fp32_t;

typedef union fp16 {
	struct {
		#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		uint16_t fraction:10;
		uint16_t exponent:5;
		uint16_t sign:1;
		# define __FP16_INITIALIZER(s, e, f) {f, e, s}
		#else
		uint16_t sign:1;
		uint16_t exponent:5;
		uint16_t fraction:10;
		# define __FP16_INITIALIZER(s, e, f) {s, e, f}
		#endif
	} __attribute__((packed));
#ifdef SUPPORT_FP16
	compat_fp16 f16;
#endif
	uint16_t i16;
#define FP16_INITIALIZER(s, e, f) {__FP16_INITIALIZER(s, e, f)}
} fp16_t;


/* https://en.wikipedia.org/wiki/Double-precision_floating-point_format */
__myconst__ fp64_t fp64_NaN = FP64_INITIALIZER(1, 0x7ff, 0xfffffffffffff);
__myconst__ fp64_t fp64_PosInf = FP64_INITIALIZER(0, 0x7ff, 0);
__myconst__ fp64_t fp64_NegInf = FP64_INITIALIZER(1, 0x7ff, 0);
__myconst__ fp64_t fp64_PosZero = FP64_INITIALIZER(0, 0, 0);
__myconst__ fp64_t fp64_NegZero = FP64_INITIALIZER(1, 0, 0);
/* ≈ 1.7976931348623157 × 10³⁰⁸ */
__myconst__ fp64_t fp64_PosMax = FP64_INITIALIZER(0, 0x7fe, 0xFFFFFFFFFFFFF);
__myconst__ fp64_t fp64_NegMax = FP64_INITIALIZER(1, 0x7fe, 0xFFFFFFFFFFFFF);
/* ≈ 2.2250738585072014 × 10⁻³⁰⁸ */
__myconst__ fp64_t fp64_PosMin = FP64_INITIALIZER(0, 1, 0);
__myconst__ fp64_t fp64_NegMin = FP64_INITIALIZER(1, 1, 0);

/* https://en.wikipedia.org/wiki/Single-precision_floating-point_format */
__myconst__ fp32_t fp32_NaN = FP32_INITIALIZER(1, 0xff, 0xff);
__myconst__ fp32_t fp32_PosInf = FP32_INITIALIZER(0, 0xff, 0);
__myconst__ fp32_t fp32_NegInf = FP32_INITIALIZER(1, 0xff, 0);
__myconst__ fp32_t fp32_PosZero = FP32_INITIALIZER(0, 0, 0);
__myconst__ fp32_t fp32_NegZero = FP32_INITIALIZER(1, 0, 0);
/**
 * See also FLT_MAX and FLT_MIN
 */
/* ≈ ±3.4028235 × 10³⁸ */
__myconst__ fp32_t fp32_PosMax = FP32_INITIALIZER(0, 0xfe, 0x7fffff);
__myconst__ fp32_t fp32_NegMax = FP32_INITIALIZER(1, 0xfe, 0x7fffff);
/* ≈ ±1.17549435 × 10⁻³⁸ */
__myconst__ fp32_t fp32_PosMin = FP32_INITIALIZER(0, 0x1, 0);
__myconst__ fp32_t fp32_NegMin = FP32_INITIALIZER(1, 0x1, 0);
__myconst__ fp32_t fp32_0dot15625 = FP32_INITIALIZER(0, 0x7c, 0x200000);

/* https://en.wikipedia.org/wiki/Half-precision_floating-point_format */
__myconst__ fp16_t fp16_NaN = FP16_INITIALIZER(1, 0x1f, 0x3ff);
__myconst__ fp16_t fp16_PosInf = FP16_INITIALIZER(0, 0x1f, 0);
__myconst__ fp16_t fp16_NegInf = FP16_INITIALIZER(1, 0x1f, 0);
__myconst__ fp16_t fp16_PosZero = FP16_INITIALIZER(0, 0, 0);
__myconst__ fp16_t fp16_NegZero = FP16_INITIALIZER(1, 0, 0);
/* ± 65504.0 */
__myconst__ fp16_t fp16_PosMax = FP16_INITIALIZER(0, 0x1e, 0x3ff);
__myconst__ fp16_t fp16_NegMax = FP16_INITIALIZER(1, 0x1e, 0x3ff);
/* ± 2^(-14) ≈ 6.103515625 × 10^(-5) */
__myconst__ fp16_t fp16_PosMin = FP16_INITIALIZER(0, 0x1, 0);
__myconst__ fp16_t fp16_NegMin = FP16_INITIALIZER(1, 0x1, 0);


#ifdef HAVE_CUDA
/**
 * From struct to host
 */
# define st2host(st, field)	({	\
		typeof(st.field) __v;	\
		cudaMemcpyFromSymbol(&__v, st, sizeof(st.field), offsetof(typeof(st), field));	\
		__v;	\
	})
# define stset(st, field, v)	do {	\
		typeof(st) __hostst = { .field = v, };	\
		cudaMemcpyToSymbol(st, &__hostst, sizeof(st));	\
	} while (0)
#else
# define st2host(st, field)	st.field
# define stset(st, field, v)	st.field = v
#endif

void binprint(const void *mem, size_t bits)
{
	size_t i;
	for (i = 0; i < bits; i++) {
		uint8_t u8 = *(uint8_t *)((const int8_t *)mem + i / 8);
		uint8_t bit = (u8 >> (i % 8) & 0x1);
		printf("%c", bit ? '1' : '0');
	}
	printf("\n");
}

/* Could use to both float and double */
double __mydevice__ fraction_value(uint64_t fraction, uint64_t nbits)
{
	uint32_t tmp, i;
	double fra = 0.0f;

	for (i = 1; i <= nbits; i++) {
		tmp = (fraction >> (nbits - i)) & 0x1;
		if (tmp == 0)
			continue;
		fra += exp2f(-1.0f * i);
	}
	return fra;
}

void __mydevice__ double_to_fp64(const double d, fp64_t *fp64)
{
	double tmp = d;
	int64_t i64 = *(int64_t *)&tmp;

	*fp64 = *(fp64_t *)&i64;
}

double __mydevice__ fp64_to_double(const fp64_t *fp64)
{
	double sign = 1 - 2 * (fp64->sign % 2);
	double e2, fra;

	if (fp64->exponent == 0) {
		if (fp64->fraction == 0) {
			return fp64->sign == 0 ? fp64_PosZero.f64 :
						 fp64_NegZero.f64;
		} else {
			e2 = exp2(-1022.0);
			fra = 0 + fraction_value(fp64->fraction, 52);
		}
	} else if (fp64->exponent == 0x7ff) {
		if (fp64->fraction == 0)
			return fp64->sign == 0 ? fp64_PosInf.f64 :
						 fp64_NegInf.f64;
		else
			return fp64_NaN.f64;
	} else {
		e2 = exp2(fp64->exponent - 1023.0);
		fra = 1 + fraction_value(fp64->fraction, 52);
	}

	return sign * e2 * fra;
}

void __myglobal__ __kernel_check_fp64(double f)
{
	double to;
	fp64_t fp64;

	double_to_fp64(f, &fp64);
	to = fp64_to_double(&fp64);

	printf("%lf vs %lf (%x %x %lx) ", f, to, fp64.sign, fp64.exponent,
		(uint64_t)fp64.fraction);

	assert(*(uint64_t *)&f == *(uint64_t *)&to && "Failed to check fp64");
}

#define check_fp64(v)	do {	\
		printf("%s: ", #v);	\
		typeof(v) ___v = v;	\
		__kernel_check_fp64 DIM (___v);	\
		mysync();	\
		binprint(&___v, sizeof(v) * 8);	\
	} while (0)


void __mydevice__ float_to_fp32(const float f, fp32_t *fp32)
{
	float tmp = f;
	int32_t i32 = *(int32_t *)&tmp;

	*fp32 = *(fp32_t *)&i32;
}

float __mydevice__ fp32_to_float(const fp32_t *fp32)
{
	float sign = 1 - 2 * (fp32->sign % 2);
	float e2, fra;

	if (fp32->exponent == 0) {
		if (fp32->fraction == 0) {
			return fp32->sign == 0 ? fp32_PosZero.f32 :
						 fp32_NegZero.f32;
		} else {
			e2 = exp2f(-126.0f);
			fra = 0 + fraction_value(fp32->fraction, 23);
		}
	} else if (fp32->exponent == 0xff) {
		if (fp32->fraction == 0)
			return fp32->sign == 0 ? fp32_PosInf.f32 :
						 fp32_NegInf.f32;
		else
			return fp32_NaN.f32;
	} else {
		e2 = exp2f(fp32->exponent - 127.0f);
		fra = 1 + fraction_value(fp32->fraction, 23);
	}

	return sign * e2 * fra;
}

void __myglobal__ __kernel_check_fp32(float f)
{
	float to;
	fp32_t fp32;

	float_to_fp32(f, &fp32);
	to = fp32_to_float(&fp32);

	printf("%f vs %f (%x %x %x) ", f, to, fp32.sign, fp32.exponent,
		fp32.fraction);

	assert(*(uint32_t *)&f == *(uint32_t *)&to && "Failed to check fp32");
}

#define check_fp32(v)	do {	\
		printf("%s: ", #v);	\
		typeof(v) ___v = v;	\
		__kernel_check_fp32 DIM (___v);	\
		mysync();	\
		binprint(&___v, sizeof(v) * 8);	\
	} while (0)

#ifdef SUPPORT_FP16
void __mydevice__ float16_to_fp16(const compat_fp16 f, fp16_t *fp16)
{
	compat_fp16 tmp = f;
	int16_t i16 = *(int16_t *)&tmp;

	*fp16 = *(fp16_t *)&i16;
}

compat_fp16 __mydevice__ fp16_to_float16(const fp16_t *fp16)
{
	compat_fp16 sign = compat_float2half(1 - 2 * (fp16->sign % 2));
	compat_fp16 e2, fra;

	if (fp16->exponent == 0) {
		if (fp16->fraction == 0) {
			return fp16->sign == 0 ? fp16_PosZero.f16 :
						 fp16_NegZero.f16;
		} else {
			e2 = compat_float2half(exp2f(-14.0f));
			fra = compat_float2half(0 + fraction_value(fp16->fraction, 10));
		}
	} else if (fp16->exponent == 0x1f) {
		if (fp16->fraction == 0)
			return fp16->sign == 0 ? fp16_PosInf.f16 :
						 fp16_NegInf.f16;
		else
			return fp16_NaN.f16;
	} else {
		e2 = compat_float2half(exp2f(fp16->exponent - 15.0f));
		fra = compat_float2half(1 + fraction_value(fp16->fraction, 10));
	}

	return sign * e2 * fra;
}

void __myglobal__ __kernel_check_fp16(compat_fp16 f)
{
	compat_fp16 to;
	fp16_t fp16;

	float16_to_fp16(f, &fp16);
	to = fp16_to_float16(&fp16);

	printf("%f vs %f (%x %x %x) ", (float)f, (float)to,
		fp16.sign, fp16.exponent, fp16.fraction);

	assert(*(uint16_t *)&f == *(uint16_t *)&to && "Failed to check fp16");
}

#define check_fp16(v)	do {	\
		printf("%s: ", #v);	\
		typeof(v) ___v = v;	\
		__kernel_check_fp16 DIM (___v);	\
		mysync();	\
		binprint(&___v, sizeof(v) * 8);	\
	} while (0)
#endif /* SUPPORT_FP16 */


void base_test(void)
{
	seperator();

	check_fp64(0);
	check_fp64(1.2);
	check_fp64(0.2);
	check_fp64(1.23456789);
	check_fp64(0.23456789);
	check_fp64(3.14159265);
	check_fp64(-3.14159265);
	check_fp64(st2host(fp64_NaN, f64));
	check_fp64(st2host(fp64_PosInf, f64));
	check_fp64(st2host(fp64_NegInf, f64));
	check_fp64(st2host(fp64_PosZero, f64));
	check_fp64(st2host(fp64_NegZero, f64));
	check_fp64(st2host(fp64_PosMax, f64));
	check_fp64(st2host(fp64_PosMin, f64));
	check_fp64(st2host(fp64_NegMax, f64));
	check_fp64(st2host(fp64_NegMin, f64));

	seperator();

	check_fp32(0);
	check_fp32(1.2f);
	check_fp32(0.2f);
	check_fp32(1.23456789f);
	check_fp32(0.23456789f);
	check_fp32(3.14159265f);
	check_fp32(-3.14159265f);
	check_fp32(st2host(fp32_NaN, f32));
	check_fp32(st2host(fp32_PosInf, f32));
	check_fp32(st2host(fp32_NegInf, f32));
	check_fp32(st2host(fp32_PosZero, f32));
	check_fp32(st2host(fp32_NegZero, f32));
	check_fp32(st2host(fp32_PosMax, f32));
	check_fp32(FLT_MAX);
	check_fp32(st2host(fp32_PosMin, f32));
	check_fp32(FLT_MIN);
	check_fp32(st2host(fp32_NegMax, f32));
	check_fp32(st2host(fp32_NegMin, f32));

#ifdef SUPPORT_FP16
	seperator();

	check_fp16(compat_float2half(0.0));
	check_fp16(compat_float2half(1.2));
	check_fp16(compat_float2half(0.2));
	check_fp16(compat_float2half(1.23456789));
	check_fp16(compat_float2half(0.23456789));
	check_fp16(compat_float2half(3.14159265));
	check_fp16(compat_float2half(-3.14159265));
	check_fp16(st2host(fp16_NaN, f16));
	check_fp16(st2host(fp16_PosInf, f16));
	check_fp16(st2host(fp16_NegInf, f16));
	check_fp16(st2host(fp16_PosZero, f16));
	check_fp16(st2host(fp16_NegZero, f16));
	check_fp16(st2host(fp16_PosMax, f16));
	check_fp16(st2host(fp16_NegMax, f16));
	check_fp16(st2host(fp16_PosMin, f16));
	check_fp16(st2host(fp16_NegMin, f16));
#endif

	reset();
}

/**
 * Testing float precision and overflow from here.
 */

/**
 * To enable computation on the GPU, we use the __device__ variable to ensure
 * that all computations occur in the GPU FP rather than on the CPU.
 *
 * If testing on the CPU, __mydevice__ is empty.
 */
__mydevice__ fp32_t overflow_fp32_rslt;
__mydevice__ fp32_t overflow_fp32_bias;
/**
 * In addition to using fp32 to save the calculation results, fp64 is also
 * used to save the calculation results in order to obtain the calculation
 * results when there is no overflow, as a comparison.
 */
__mydevice__ fp64_t overflow_fp64_rslt;

void __myglobal__ __kernel_mul_overflow_mul_fp32(void)
{
	overflow_fp32_rslt.f32 *= overflow_fp32_bias.f32;
	overflow_fp64_rslt.f64 *= overflow_fp32_bias.f32;
}

void __myglobal__ __kernel_add_overflow_add_fp32(void)
{
	overflow_fp32_rslt.f32 += overflow_fp32_bias.f32;
	overflow_fp64_rslt.f64 += overflow_fp32_bias.f32;
}

#ifdef __HPCC__
# pragma clang diagnostic push
/* warning: reference to __device__ variable 'overflow_fp64_rslt' in __host__ function */
# pragma clang diagnostic ignored "-Whpcc-compat"
#endif
void overflow_mul_fp32(void)
{
	float a = st2host(fp32_PosMax, f32) / 2.0f;

	stset(overflow_fp32_rslt, f32, a);
	stset(overflow_fp32_bias, f32, 1.15f);
	stset(overflow_fp64_rslt, f64, a);

	for (int i = 0; i < 10; i++) {
		__kernel_mul_overflow_mul_fp32 DIM ();

		seperator();
		printf("=========== mul %d ==========\n", i);
		check_fp32(st2host(overflow_fp32_rslt, f32));
		check_fp64(st2host(overflow_fp64_rslt, f64));
		reset();
		mysync();
	}
}

void overflow_add_fp32(void)
{
	float a = st2host(fp32_PosMax, f32) / 2.0f;
	float bias = st2host(fp32_PosMax, f32) / 9.0f;

	stset(overflow_fp32_rslt, f32, a);
	stset(overflow_fp32_bias, f32, bias);
	stset(overflow_fp64_rslt, f64, a);

	for (int i = 0; i < 10; i++) {
		__kernel_add_overflow_add_fp32 DIM ();

		seperator();
		printf("=========== add %d ==========\n", i);
		check_fp32(st2host(overflow_fp32_rslt, f32));
		check_fp64(st2host(overflow_fp64_rslt, f64));
		reset();
		mysync();
	}
}
#ifdef __HPCC__
# pragma clang diagnostic pop
#endif

void overflow(void)
{
	seperator();

	check_fp32(st2host(fp32_PosMax, f32));
	check_fp32(st2host(fp32_PosMax, f32) + 0.1f);
	check_fp32(st2host(fp32_PosMax, f32) - 0.1f);
	check_fp32(st2host(fp32_PosMax, f32) + 0.2f);
	check_fp32(st2host(fp32_PosMax, f32) / 2.0f);

	seperator();

	check_fp32(st2host(fp32_PosMax, f32) * 1.0f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.00000000001f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.0000000001f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.000000001f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.00000001f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.000000011f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.00000005f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.000000055f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.000000058f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.000000059f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.0000000595f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.0000000596f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.000000059604f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.0000000596045f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.0000000596046f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.00000005960463f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.00000005960464f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.000000059604644f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.0000000596046445f);

	seperator();
	/**
	 * Since here, value become Inf
	 * CPU: Intel i7-10710U, AMD EPYC 7763
	 * GPU: Mars X203
	 */
	check_fp32(st2host(fp32_PosMax, f32) * 1.0000000596046449f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.000000059604645f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.00000005960465f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.00000005960469f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.0000000596047f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.0000000596049f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.000000059605f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.000000059606f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.000000059609f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.00000005961f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.00000005963f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.00000005965f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.00000005969f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.0000000597f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.0000000598f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.0000000599f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.00000006f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.00000007f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.00000009f);
	check_fp32(st2host(fp32_PosMax, f32) * 1.0000001f);

	seperator();

	overflow_mul_fp32();
	overflow_add_fp32();

	reset();
}

int main(int argc, char *argv[])
{
	assert(sizeof(fp64_t) == 8 && "Bad size of fp64");
	assert(sizeof(fp32_t) == 4 && "Bad size of fp32");
	assert(sizeof(fp16_t) == 2 && "Bad size of fp16");

	base_test();

	overflow();

	return 0;
}
