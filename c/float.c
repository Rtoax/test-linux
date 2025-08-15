// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * Refs:
 * - https://en.wikipedia.org/wiki/IEEE_754-2008_revision
 * - https://en.wikipedia.org/wiki/Half-precision_floating-point_format
 * - https://en.wikipedia.org/wiki/Single-precision_floating-point_format
 * - https://en.wikipedia.org/wiki/Double-precision_floating-point_format
 */
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <byteswap.h>

#if defined(__HPCC__) || defined(__NVCC__)
# define HAVE_CUDA	1
  /* Metax has CUDA-compatible APIs */
# if defined(__HPCC__)	/* MetaX */
#  include <hccl.h>
#  include <hpcc_fp16.h>
# elif defined(__NVCC__)	/* Nvidia */
#  include <cuda_fp16.h>
# endif
#endif

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
	};
	double f64;
	uint64_t i64;
#define FP64_INITIALIZER(s, e, f) {__FP64_INITIALIZER(s, e, f)}
#define FP64(s, e, f) (((s & 0x1UL) << 63) | ((e & 0x7ffUL) << 52) | ((f & 0xfffffffffffffUL)))
} __attribute__((packed)) fp64_t;

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
	};
	float f32;
	uint32_t i32;
#define FP32_INITIALIZER(s, e, f) {__FP32_INITIALIZER(s, e, f)}
} __attribute__((packed)) fp32_t;

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
	};
	_Float16 f16;
	uint16_t i16;
#define FP16_INITIALIZER(s, e, f) {__FP16_INITIALIZER(s, e, f)}
} __attribute__((packed)) fp16_t;

/* https://en.wikipedia.org/wiki/Single-precision_floating-point_format */
const fp32_t fp32_NaN = FP32_INITIALIZER(1, 0xff, 0xff);
const fp32_t fp32_PosInf = FP32_INITIALIZER(0, 0xff, 0);
const fp32_t fp32_NegInf = FP32_INITIALIZER(1, 0xff, 0);
const fp32_t fp32_PosZero = FP32_INITIALIZER(0, 0, 0);
const fp32_t fp32_NegZero = FP32_INITIALIZER(1, 0, 0);
const fp32_t fp32_0dot15625 = FP32_INITIALIZER(0, 0x7c, 0x200000);

/* https://en.wikipedia.org/wiki/Double-precision_floating-point_format */
const fp64_t fp64_NaN = FP64_INITIALIZER(1, 0x7ff, 0xfffffffffffff);
const fp64_t fp64_PosInf = FP64_INITIALIZER(0, 0x7ff, 0);
const fp64_t fp64_NegInf = FP64_INITIALIZER(1, 0x7ff, 0);
const fp64_t fp64_PosZero = FP64_INITIALIZER(0, 0, 0);
const fp64_t fp64_NegZero = FP64_INITIALIZER(1, 0, 0);


/* Could use to both float and double */
double fraction_value(uint64_t fraction, uint64_t nbits)
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

void double_to_fp64(const double d, fp64_t *fp64)
{
	double tmp = d;
	int64_t i64 = *(int64_t *)&tmp;

	*fp64 = *(fp64_t *)&i64;
}

double fp64_to_double(const fp64_t *fp64)
{
	double f;
	int64_t i64 = *(int64_t *)fp64;

	f = *(double *)&i64;
	(void)f;

	double sign = 1 - 2 * (fp64->sign % 2);
	double e2, fra;

	if (fp64->exponent == 0) {
		if (fp64->fraction == 0) {
			return sign * 0.0;
		} else {
			e2 = exp2(-1022.0);
			fra = 0 + fraction_value(fp64->fraction, 52);
		}
	} else if (fp64->exponent == 0x7ff) {
		if (fp64->fraction == 0)
			return fp64->sign == 0 ? *(double *)&fp64_PosInf :
						 *(double *)&fp64_NegInf;
		else
			return *(double *)&fp64_NaN;
	} else {
		e2 = exp2(fp64->exponent - 1023.0);
		fra = 1 + fraction_value(fp64->fraction, 52);
	}

	return sign * e2 * fra;
}

void check_fp64(double f)
{
	double to;
	fp64_t fp64;

	double_to_fp64(f, &fp64);
	to = fp64_to_double(&fp64);

	printf("%lf vs %lf (%x %x %lx)\n", f, to, fp64.sign, fp64.exponent, (uint64_t)fp64.fraction);
}

void float_to_fp32(const float f, fp32_t *fp32)
{
	float tmp = f;
	int32_t i32 = *(int32_t *)&tmp;

	*fp32 = *(fp32_t *)&i32;
}

float fp32_to_float(const fp32_t *fp32)
{
	float f;
	int32_t i32 = *(int32_t *)fp32;

	f = *(float *)&i32;
	(void)f;

	float sign = 1 - 2 * (fp32->sign % 2);
	float e2, fra;

	if (fp32->exponent == 0) {
		if (fp32->fraction == 0) {
			return sign * 0.0f;
		} else {
			e2 = exp2f(-126.0f);
			fra = 0 + fraction_value(fp32->fraction, 23);
		}
	} else if (fp32->exponent == 0xff) {
		if (fp32->fraction == 0)
			return fp32->sign == 0 ? *(float *)&fp32_PosInf :
						 *(float *)&fp32_NegInf;
		else
			return *(float *)&fp32_NaN;
	} else {
		e2 = exp2f(fp32->exponent - 127.0f);
		fra = 1 + fraction_value(fp32->fraction, 23);
	}

	return sign * e2 * fra;
}

void check_fp32(float f)
{
	float to;
	fp32_t fp32;

	float_to_fp32(f, &fp32);
	to = fp32_to_float(&fp32);

	printf("%f vs %f (%x %x %x)\n", f, to, fp32.sign, fp32.exponent, fp32.fraction);
}

int main(void)
{
	assert(sizeof(fp64_t) == 8 && "Bad size of fp64");
	assert(sizeof(fp32_t) == 4 && "Bad size of fp32");
	assert(sizeof(fp16_t) == 2 && "Bad size of fp16");

	check_fp32(0);
	check_fp32(1.2f);
	check_fp32(0.2f);
	check_fp32(1.23456789f);
	check_fp32(0.23456789f);
	check_fp32(3.14159265f);
	check_fp32(-3.14159265f);
	check_fp32(fp32_NaN.f32);
	check_fp32(fp32_PosInf.f32);
	check_fp32(fp32_NegInf.f32);
	check_fp32(fp32_PosZero.f32);
	check_fp32(fp32_NegZero.f32);

	check_fp64(0);
	check_fp64(1.2);
	check_fp64(0.2);
	check_fp64(1.23456789);
	check_fp64(0.23456789);
	check_fp64(3.14159265);
	check_fp64(-3.14159265);
	check_fp64(fp64_NaN.f64);
	check_fp64(fp64_PosInf.f64);
	check_fp64(fp64_NegInf.f64);
	check_fp64(fp64_PosZero.f64);
	check_fp64(fp64_NegZero.f64);

#ifdef HAVE_CUDA
	half f16 = __float2half(1.0f);
	// TODO
#endif

	return 0;
}
