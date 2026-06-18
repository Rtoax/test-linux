// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025-2026 Rong Tao */
/**
 * Test various floating point precisions on various hardware such as CPU and
 * GPU. Different hardware handles precision and overflow differently.
 *
 * Standard:
 * - ISO/IEC 60559
 * - IEEE 754
 *
 * Floating-point formats:
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
 * Precision:
 *
 * commit ebff39b53cbf ("float.c: precision compare between CPU and different GPUs") Mars & Nvidia H800
 * commit f01d19e54ef4 ("float.c: precision compare between CPU and GPU (lingspeed, NVIDIA GB10)")
 *
 * Macros in this source code file:
 *
 * - SUPPORT__Float16: compiler support _Float16;
 * - SUPPORT___fp16: compiler support __fp16
 * - SUPPORT___bf16: compiler support __bf16
 * - SUPPORT___float128: compiler support __float128
 *
 * - SUPPORT_FP16: support _Float16 or cuda's half;
 * - SUPPORT_BF16: support __bf16 or cuda's __nv_bfloat16, or hpcc's __hpcc_bfloat16;
 *
 * Refs:
 * - https://en.wikipedia.org/wiki/IEEE_754-2008_revision
 * - https://en.wikipedia.org/wiki/Minifloat
 * - https://en.wikipedia.org/wiki/Half-precision_floating-point_format
 * - https://en.wikipedia.org/wiki/Bfloat16_floating-point_format
 * - https://en.wikipedia.org/wiki/Single-precision_floating-point_format
 * - https://en.wikipedia.org/wiki/Double-precision_floating-point_format
 * - https://en.wikipedia.org/wiki/Quadruple-precision_floating-point_format
 * - https://github.com/Maratyszcza/FP16
 * - https://clang.llvm.org/docs/LanguageExtensions.html
 */
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <byteswap.h>
#include <float.h>
#include <string.h>

#if defined(__HPCC__) || defined(__LUCA__) || defined(__NVCC__) || \
    defined(__HIPCC__)
# define IS_CUDA_COMPAT_COMPILER	1
# include <cuda_fp16.h>
# include <cuda_bf16.h>
# include <cuda_runtime.h>
# if defined(__HPCC__)	/* MetaX */
#  ifndef SUPPORT__Float16
#   define SUPPORT__Float16 /* HPCC always support _Float16 */
#  endif
# elif defined(__LUCA__)
#  ifndef SUPPORT__Float16
#   define SUPPORT__Float16 /* LUCA always support _Float16 */
#  endif
# elif defined(__NVCC__)	/* Nvidia */
#  ifdef SUPPORT__Float16
#   undef SUPPORT__Float16
#   warning Error: Internal Compiler Error (codegen): "unsupported float variant!"
#  endif
# elif defined(__HIPCC__)	/* AMD ROCm HIP */
# endif
# define CALL(func, ...) func<<<1, 1>>>(__VA_ARGS__)
# define devSync() (void)cudaDeviceSynchronize()
# define DEVICE "GPU"
#else
# define CALL(func, ...) func(__VA_ARGS__)
# define __device__
# define __global__
# define __constant__ const
# define devSync()
# define DEVICE "CPU"
#endif

#define TEST(title, n) \
	printf("=========== %s on %s (%ld) ==========\n", title, DEVICE, n);

/**
 * Note: Use _Float16 first
 */
#ifdef SUPPORT__Float16
# define SUPPORT_FP16	1
# define compat_fp16	_Float16
# define compat_half2float(v)	((float)v)
# define compat_float2half(v)	((_Float16)v)
# define compat_fp16_exp2(v) exp2f(v)
#elif defined(IS_CUDA_COMPAT_COMPILER)
# define SUPPORT_FP16	1
# define compat_fp16	half
# define compat_half2float(v)	__half2float(v)
# define compat_float2half(v)	__float2half(v)
# define compat_fp16_exp2(v) hexp2(v)
#endif

#ifdef SUPPORT___bf16
/**
 * Note: gcc >= 13 __bf16 arithmetic support.
 *
 * gcc git://gcc.gnu.org/git/gcc.git
 * - commit 0a329ecf1137 ("libgcc, Darwin: Update symbol exports to include bitint and bf.")
 * - commit 13071c3c7d1b ("aarch64: Add bfloat16_t support for aarch64")
 * - commit c2565a31c162 ("middle-end, c++, i386, libgcc: std::bfloat16_t and __bf16 arithmetic support")
 *
 * llvm https://github.com/llvm/llvm-project
 * - commit a7a7e9572022 ("[AMDGPU][Clang] Support bfloat16 arithmetic. (#147541)")
 * - commit e62175736551 ("[Clang][BFloat16] Upgrade __bf16 to arithmetic type, change mangling, and extend excess precision support")
 */
# if (defined(__clang__) && (__clang_major__ >= 20)) || \
     (defined(__GNUC__) && (__GNUC__ >= 13))
#  pragma message "Support bfloat16 arithmetic"
#  define SUPPORT_BF16
# endif
# define compat_bf16	__bf16
# define compat_bf16tofloat(v)	((float)v)
# define compat_floattobf16(v)	((__bf16)v)
#elif defined(IS_CUDA_COMPAT_COMPILER)
# define SUPPORT_BF16
# if defined(__NVCC__)	/* Nvidia */
#  define compat_bf16	__nv_bfloat16
# elif defined(__HIPCC__)
#  define compat_bf16	__hip_bfloat16
# elif defined(__HPCC__)
#  define compat_bf16	__hpcc_bfloat16
# elif defined(__LUCA__)
#  define compat_bf16	__luca_bfloat16
# endif
# define compat_bf16tofloat(v)	__bfloat162float(v)
# define compat_floattobf16(v)	__float2bfloat16(v)
#endif

#if defined(__HIPCC__) && ((HIP_VERSION_MAJOR < 5) || \
			   (HIP_VERSION_MAJOR == 5 && HIP_VERSION_MINOR <= 7))
# ifdef SUPPORT_BF16
#  undef SUPPORT_BF16
# endif
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

static struct {
	bool nocolor;
	bool version;
	/**
	 * Testing types, default test all
	 */
	bool fp64, fp32, fp16, bf16;
} env = {
	.nocolor = false,
	.version = false,
	.fp64 = true,
	.fp32 = true,
	.fp16 = true,
	.bf16 = true,
};

static const char *const version = "v1.6.0";

#define seperator()                                                            \
	do {                                                                   \
		if (env.nocolor) {                                             \
			printf("-----------------------------------------\n"); \
		} else {                                                       \
			printf("%s%s", reset,                                  \
			       ansi[ansi_idx++ % ARRAY_SIZE(ansi)]);           \
		}                                                              \
	} while (0)
#define reset()                      \
	do {                         \
		if (env.nocolor)     \
			break;       \
		printf("%s", reset); \
		ansi_idx++;          \
	} while (0)

typedef union fp128 {
	struct {
		#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		__uint128_t fraction:112;
		uint64_t exponent:15;
		uint64_t sign:1;
		# define __FP128_INITIALIZER(s, e, f) {f, e, s}
		#else
		uint64_t sign:1;
		uint64_t exponent:15;
		__uint128_t fraction:112;
		# define __F128_INITIALIZER(s, e, f) {s, e, f}
		#endif
	} __attribute__((packed));
#ifdef SUPPORT___float128
	__float128 f128;
#endif
} fp128_t;

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
#if defined(__clang__) || defined(SUPPORT___fp16)
	/**
	 * __fp16 is supported on all targets.
	 * The special semantics of this type mean that no arithmetic is ever
	 * performed directly on __fp16 values.
	 * from: https://clang.llvm.org/docs/LanguageExtensions.html
	 */
	__fp16 fp16;
#endif
	uint16_t i16;
#define FP16_INITIALIZER(s, e, f) {__FP16_INITIALIZER(s, e, f)}
} fp16_t;

typedef union bfloat16 {
	struct {
		#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		uint16_t fraction:7;
		uint16_t exponent:8;
		uint16_t sign:1;
		# define __BF16_INITIALIZER(s, e, f) {f, e, s}
		#else
		uint16_t sign:1;
		uint16_t exponent:8;
		uint16_t fraction:7;
		# define __BF16_INITIALIZER(s, e, f) {s, e, f}
		#endif
	} __attribute__((packed));
#ifdef SUPPORT_BF16
	compat_bf16 f16;
#endif
	uint16_t i16;
#define BF16_INITIALIZER(s, e, f) {__BF16_INITIALIZER(s, e, f)}
} bf16_t;


/* https://en.wikipedia.org/wiki/Double-precision_floating-point_format */
__constant__ fp64_t fp64_NaN = FP64_INITIALIZER(1, 0x7ff, 0xfffffffffffff);
/* See also __builtin_huge_val() */
__constant__ fp64_t fp64_PosInf = FP64_INITIALIZER(0, 0x7ff, 0);
__constant__ fp64_t fp64_NegInf = FP64_INITIALIZER(1, 0x7ff, 0);
__constant__ fp64_t fp64_PosZero = FP64_INITIALIZER(0, 0, 0);
__constant__ fp64_t fp64_NegZero = FP64_INITIALIZER(1, 0, 0);
/* ≈ 1.7976931348623157 × 10³⁰⁸ */
__constant__ fp64_t fp64_PosMax = FP64_INITIALIZER(0, 0x7fe, 0xFFFFFFFFFFFFF);
__constant__ fp64_t fp64_NegMax = FP64_INITIALIZER(1, 0x7fe, 0xFFFFFFFFFFFFF);
/* ≈ 2.2250738585072014 × 10⁻³⁰⁸ */
__constant__ fp64_t fp64_PosMin = FP64_INITIALIZER(0, 1, 0);
__constant__ fp64_t fp64_NegMin = FP64_INITIALIZER(1, 1, 0);

/* https://en.wikipedia.org/wiki/Single-precision_floating-point_format */
__constant__ fp32_t fp32_NaN = FP32_INITIALIZER(1, 0xff, 0xff);
__constant__ fp32_t fp32_PosOne = FP32_INITIALIZER(0, 0x7f, 0);
__constant__ fp32_t fp32_PosInf = FP32_INITIALIZER(0, 0xff, 0);
__constant__ fp32_t fp32_NegInf = FP32_INITIALIZER(1, 0xff, 0);
__constant__ fp32_t fp32_PosZero = FP32_INITIALIZER(0, 0, 0);
__constant__ fp32_t fp32_NegZero = FP32_INITIALIZER(1, 0, 0);
/**
 * See also FLT_MAX and FLT_MIN
 */
/* ≈ ±3.4028235 × 10³⁸ */
__constant__ fp32_t fp32_PosMax = FP32_INITIALIZER(0, 0xfe, 0x7fffff);
__constant__ fp32_t fp32_NegMax = FP32_INITIALIZER(1, 0xfe, 0x7fffff);
/* ≈ ±1.17549435 × 10⁻³⁸ */
__constant__ fp32_t fp32_PosMin = FP32_INITIALIZER(0, 0x1, 0);
__constant__ fp32_t fp32_NegMin = FP32_INITIALIZER(1, 0x1, 0);
__constant__ fp32_t fp32_0dot15625 = FP32_INITIALIZER(0, 0x7c, 0x200000);

/* https://en.wikipedia.org/wiki/Half-precision_floating-point_format */
/**
 * #define CUDART_NAN_FP16 __ushort_as_half((unsigned short)0x7FFFU)
 */
__constant__ fp16_t fp16_NaN = FP16_INITIALIZER(1, 0x1f, 0x3ff);
/**
 * #define CUDART_INF_FP16 __ushort_as_half((unsigned short)0x7C00U)
 */
__constant__ fp16_t fp16_PosInf = FP16_INITIALIZER(0, 0x1f, 0);
__constant__ fp16_t fp16_NegInf = FP16_INITIALIZER(1, 0x1f, 0);
/**
 * #define CUDART_ZERO_FP16 __ushort_as_half((unsigned short)0x0000U)
 * #define CUDART_NEG_ZERO_FP16 __ushort_as_half((unsigned short)0x8000U)
 */
__constant__ fp16_t fp16_PosZero = FP16_INITIALIZER(0, 0, 0);
__constant__ fp16_t fp16_NegZero = FP16_INITIALIZER(1, 0, 0);
/**
 * #define CUDART_MAX_NORMAL_FP16 __ushort_as_half((unsigned short)0x7BFFU)
 * #define CUDART_MIN_DENORM_FP16 __ushort_as_half((unsigned short)0x0001U)
 */
/* ± 65504.0 */
__constant__ fp16_t fp16_PosMax = FP16_INITIALIZER(0, 0x1e, 0x3ff);
__constant__ fp16_t fp16_NegMax = FP16_INITIALIZER(1, 0x1e, 0x3ff);
/* ± 2^(-14) ≈ 6.103515625 × 10^(-5) */
__constant__ fp16_t fp16_PosMin = FP16_INITIALIZER(0, 0x1, 0);
__constant__ fp16_t fp16_NegMin = FP16_INITIALIZER(1, 0x1, 0);

/* Quiet NaN */
__constant__ bf16_t bf16_qNaN = BF16_INITIALIZER(0, 0xff, 0x7f);
/* Signaling NaN */
__constant__ bf16_t bf16_sNaN = BF16_INITIALIZER(0, 0xff, 0x3f);
/* default use qNaN */
__constant__ bf16_t bf16_NaN = BF16_INITIALIZER(0, 0xff, 0x7f);
__constant__ bf16_t bf16_PosOne = BF16_INITIALIZER(0, 0x7f, 0);
__constant__ bf16_t bf16_PosZero = BF16_INITIALIZER(0, 0, 0);
__constant__ bf16_t bf16_NegZero = BF16_INITIALIZER(1, 0, 0);
__constant__ bf16_t bf16_PosInf = BF16_INITIALIZER(0, 0xff, 0);
__constant__ bf16_t bf16_NegInf = BF16_INITIALIZER(1, 0xff, 0);
__constant__ bf16_t bf16_PosMax = BF16_INITIALIZER(0, 0xfe, 0x7f);
__constant__ bf16_t bf16_NegMax = BF16_INITIALIZER(1, 0xfe, 0x7f);
__constant__ bf16_t bf16_PosMin = BF16_INITIALIZER(0, 0x1, 0);
__constant__ bf16_t bf16_NegMin = BF16_INITIALIZER(1, 0x1, 0);

#ifdef IS_CUDA_COMPAT_COMPILER
/**
 * From struct to host
 */
# define st2host(st, field)                                              \
	({                                                               \
		typeof(st.field) __v;                                    \
		(void)cudaMemcpyFromSymbol(&__v, st, sizeof(st.field),   \
					   offsetof(typeof(st), field)); \
		__v;                                                     \
	})
# define stset(st, type, field, v)                                   \
	do {                                                         \
		type __hostst = {                                    \
			.field = v,                                  \
		};                                                   \
		(void)cudaMemcpyToSymbol(st, &__hostst, sizeof(st)); \
	} while (0)
#else
# define st2host(st, field) st.field
# define stset(st, type, field, v) st.field = v
#endif

static void binprint(const void *mem, size_t bits)
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
double __device__ fraction_value(uint64_t fraction, uint64_t nbits)
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

void __device__ double_to_fp64(const double d, fp64_t *fp64)
{
	double tmp = d;
	int64_t i64 = *(int64_t *)&tmp;

	*fp64 = *(fp64_t *)&i64;
}

double __device__ fp64_to_double(const fp64_t *fp64)
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

void __global__ __check_fp64(double f)
{
	double to;
	fp64_t fp64;

	double_to_fp64(f, &fp64);
	to = fp64_to_double(&fp64);

	printf("%.17lf vs %.17lf (%x %x %lx) ", f, to, fp64.sign, fp64.exponent,
	       (uint64_t)fp64.fraction);

	assert(*(uint64_t *)&f == *(uint64_t *)&to && "Failed to check fp64");
}

#define check_fp64(v)                           \
	do {                                    \
		printf("%s: ", #v);             \
		typeof(v) ___v = v;             \
		CALL(__check_fp64, ___v);       \
		devSync();                      \
		binprint(&___v, sizeof(v) * 8); \
	} while (0)

void __device__ float_to_fp32(const float f, fp32_t *fp32)
{
	float tmp = f;
	int32_t i32 = *(int32_t *)&tmp;

	*fp32 = *(fp32_t *)&i32;
}

float __device__ fp32_to_float(const fp32_t *fp32)
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

void __global__ __check_fp32(float f)
{
	float to;
	fp32_t fp32;

	float_to_fp32(f, &fp32);
	to = fp32_to_float(&fp32);

	printf("%.17f vs %.17f (%x %x %x) ", f, to, fp32.sign, fp32.exponent,
	       fp32.fraction);

	assert(*(uint32_t *)&f == *(uint32_t *)&to && "Failed to check fp32");
}

#define check_fp32(v)                           \
	do {                                    \
		printf("%s: ", #v);             \
		typeof(v) ___v = v;             \
		CALL(__check_fp32, ___v);       \
		devSync();                      \
		binprint(&___v, sizeof(v) * 8); \
	} while (0)

#ifdef SUPPORT_FP16
void __device__ float16_to_fp16(const compat_fp16 f, fp16_t *fp16)
{
	compat_fp16 tmp = f;
	int16_t i16 = *(int16_t *)&tmp;

	*fp16 = *(fp16_t *)&i16;
}

compat_fp16 __device__ fp16_to_float16(const fp16_t *fp16)
{
	compat_fp16 sign = compat_float2half(1 - 2 * (fp16->sign % 2));
	compat_fp16 e2, fra;

	if (fp16->exponent == 0) {
		if (fp16->fraction == 0) {
			return fp16->sign == 0 ? fp16_PosZero.f16 :
						 fp16_NegZero.f16;
		} else {
			e2 = compat_fp16_exp2(compat_float2half(-14.0f));
			fra = compat_float2half(
				0 + fraction_value(fp16->fraction, 10));
		}
	} else if (fp16->exponent == 0x1f) {
		if (fp16->fraction == 0)
			return fp16->sign == 0 ? fp16_PosInf.f16 :
						 fp16_NegInf.f16;
		else
			return fp16_NaN.f16;
	} else {
		e2 = compat_fp16_exp2(
			compat_float2half(fp16->exponent - 15.0f));
		fra = compat_float2half(1 + fraction_value(fp16->fraction, 10));
	}

	return sign * e2 * fra;
}

void __global__ __kernel_check_fp16(compat_fp16 f)
{
	compat_fp16 to;
	fp16_t fp16;

	float16_to_fp16(f, &fp16);
	to = fp16_to_float16(&fp16);

	printf("%.17f vs %.17f (%x %x %x) ", (float)f, (float)to, fp16.sign,
	       fp16.exponent, fp16.fraction);

	assert(*(uint16_t *)&f == *(uint16_t *)&to && "Failed to check fp16");
}

#define check_fp16(v)                            \
	do {                                     \
		printf("%s: ", #v);              \
		typeof(v) ___v = v;              \
		CALL(__kernel_check_fp16, ___v); \
		devSync();                       \
		binprint(&___v, sizeof(v) * 8);  \
	} while (0)
#endif /* SUPPORT_FP16 */

#ifdef SUPPORT_BF16
void __device__ bfloat16_to_bf16(const compat_bf16 f, bf16_t *bf16)
{
	compat_bf16 tmp = f;
	int16_t i16 = *(int16_t *)&tmp;

	*bf16 = *(bf16_t *)&i16;
}

compat_bf16 __device__ bf16_to_bfloat16(const bf16_t *bf16)
{
	compat_bf16 sign = compat_floattobf16(1 - 2 * (bf16->sign % 2));
	compat_bf16 e2, fra;

	if (bf16->exponent == 0) {
		if (bf16->fraction == 0) {
			return bf16->sign == 0 ? bf16_PosZero.f16 :
						 bf16_NegZero.f16;
		} else {
			e2 = compat_floattobf16(exp2f(-126.0f));
			fra = compat_floattobf16(
				0 + fraction_value(bf16->fraction, 7));
		}
	} else if (bf16->exponent == 0xff) {
		if (bf16->fraction == 0)
			return bf16->sign == 0 ? bf16_PosInf.f16 :
						 bf16_NegInf.f16;
		else
			return bf16_NaN.f16;
	} else {
		e2 = compat_floattobf16(exp2f(bf16->exponent - 127.0f));
		fra = compat_floattobf16(1 + fraction_value(bf16->fraction, 7));
	}

	return sign * e2 * fra;
}

void __global__ __check_bf16(compat_bf16 f)
{
	compat_bf16 to;
	bf16_t bf16;

	bfloat16_to_bf16(f, &bf16);
	to = bf16_to_bfloat16(&bf16);

	printf("%f vs %f (%x %x %x) ", compat_bf16tofloat(f),
		compat_bf16tofloat(to),
		bf16.sign, bf16.exponent, bf16.fraction);

	assert(*(uint16_t *)&f == *(uint16_t *)&to && "Failed to check bf16");
}

#define check_bf16(v)                           \
	do {                                    \
		printf("%s: ", #v);             \
		typeof(v) ___v = v;             \
		CALL(__check_bf16, ___v);       \
		devSync();                      \
		binprint(&___v, sizeof(v) * 8); \
	} while (0)
#endif /* SUPPORT_BF16 */

void base_tests(void)
{
	if (env.fp64) {
		seperator();
		check_fp64(0);
		check_fp64(1.2);
		check_fp64(0.2);
		check_fp64(1.23456789);
		check_fp64(0.23456789);
		check_fp64(1.234568);
		check_fp64(0.234568);
		check_fp64(3.14159265);
		check_fp64(-3.14159265);
		check_fp64(123456789123456789.123456789123456789);
		check_fp64(DBL_MIN);
		check_fp64(-DBL_MIN);
		check_fp64(DBL_MAX);
		check_fp64(-DBL_MAX);
		check_fp64(st2host(fp64_NaN, f64));
		check_fp64(st2host(fp64_PosInf, f64));
		check_fp64(st2host(fp64_NegInf, f64));
		check_fp64(__builtin_huge_val());
		check_fp64(__builtin_inf());
		check_fp64(st2host(fp64_PosZero, f64));
		check_fp64(st2host(fp64_NegZero, f64));
		check_fp64(st2host(fp64_PosMax, f64));
		check_fp64(st2host(fp64_PosMin, f64));
		check_fp64(st2host(fp64_NegMax, f64));
		check_fp64(st2host(fp64_NegMin, f64));
	}

	if (env.fp32) {
		seperator();
		check_fp32(0);
		check_fp32(1);
		check_fp32(1.2f);
		check_fp32(0.2f);
		check_fp32(1.2345678f);
		check_fp32(0.2345678f);
		check_fp32(1.23456789f);
		check_fp32(0.23456789f);
		check_fp32(3.14159265f);
		check_fp32(-3.14159265f);
		check_fp32(123456789123456789.123456789123456789);
		check_fp32(FLT_MIN);
		check_fp32(-FLT_MIN);
		check_fp32(FLT_MAX);
		check_fp32(-FLT_MAX);
		check_fp32(st2host(fp32_PosOne, f32));
		check_fp32(st2host(fp32_NaN, f32));
		check_fp32(st2host(fp32_PosInf, f32));
		check_fp32(st2host(fp32_NegInf, f32));
		check_fp32(st2host(fp32_PosZero, f32));
		check_fp32(st2host(fp32_NegZero, f32));
		check_fp32(st2host(fp32_PosMax, f32));
		check_fp32(st2host(fp32_PosMin, f32));
		check_fp32(st2host(fp32_NegMax, f32));
		check_fp32(st2host(fp32_NegMin, f32));
	}

#ifdef SUPPORT_FP16
	if (env.fp16) {
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
	}
#endif

#ifdef SUPPORT_BF16
	if (env.bf16) {
		seperator();
		check_bf16(compat_floattobf16(0));
		check_bf16(compat_floattobf16(1.0));
		check_bf16(compat_floattobf16(3.141592653f));
		check_bf16(compat_floattobf16(-3.141592653f));
		check_bf16(st2host(bf16_PosOne, f16));
		check_bf16(st2host(bf16_NaN, f16));
		check_bf16(st2host(bf16_PosZero, f16));
		check_bf16(st2host(bf16_NegZero, f16));
		check_bf16(st2host(bf16_PosInf, f16));
		check_bf16(st2host(bf16_NegInf, f16));
	}
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
 * If testing on the CPU, __device__ is empty.
 */
#define DATA_ARRAY_SIZE	1000

__device__ fp64_t data_fp64;
__device__ fp64_t data_fp64_weight;
__device__ fp64_t data_fp64_bias;
__device__ fp64_t data_fp64_arr[DATA_ARRAY_SIZE];
__device__ fp64_t data_fp64_weight_arr[DATA_ARRAY_SIZE];
__device__ fp64_t data_fp64_bias_arr[DATA_ARRAY_SIZE];

__device__ fp32_t data_fp32;
__device__ fp32_t data_fp32_weight;
__device__ fp32_t data_fp32_bias;
__device__ fp32_t data_fp32_arr[DATA_ARRAY_SIZE];
__device__ fp32_t data_fp32_weight_arr[DATA_ARRAY_SIZE];
__device__ fp32_t data_fp32_bias_arr[DATA_ARRAY_SIZE];

__device__ fp16_t data_fp16;
__device__ fp16_t data_fp16_weight;
__device__ fp16_t data_fp16_bias;
__device__ fp16_t data_fp16_arr[DATA_ARRAY_SIZE];
__device__ fp16_t data_fp16_weight_arr[DATA_ARRAY_SIZE];
__device__ fp16_t data_fp16_bias_arr[DATA_ARRAY_SIZE];

/**
 * In addition to using fp32 to save the calculation results, fp64 is also
 * used to save the calculation results in order to obtain the calculation
 * results when there is no overflow, as a comparison.
 */
__device__ fp64_t rslt_fp64;
__device__ fp32_t rslt_fp32;

void __global__ init_data_fp64(double init)
{
	data_fp64.f64 = init;
	data_fp64_weight.f64 = init;
	data_fp64_bias.f64 = init;
}

void __global__ init_data_arr_fp64(size_t size)
{
	for (size_t i = 0; i < size; i++) {
		data_fp64_arr[i].f64 = i * 1000.0;
		data_fp64_weight_arr[i].f64 = i * 1000.0;
		data_fp64_bias_arr[i].f64 = i * 1000.0;
	}
}

void __global__ init_data_arr_fp32(size_t size)
{
	for (size_t i = 0; i < size; i++) {
		data_fp32_arr[i].f32 = i * 1000.f;
		data_fp32_weight_arr[i].f32 = i * 1000.f;
		data_fp32_bias_arr[i].f32 = i * 1000.f;
	}
}

#ifdef SUPPORT_FP16
void __global__ init_data_arr_fp16(size_t size, float init)
{
	for (size_t i = 0; i < size; i++) {
		data_fp16_arr[i].f16 = compat_float2half(init);
		data_fp16_weight_arr[i].f16 = compat_float2half(init);
		data_fp16_bias_arr[i].f16 = compat_float2half(init);
	}
}
#endif

void __global__ __kernel_mul_w_fp32(void)
{
	data_fp32.f32 *= data_fp32_weight.f32;
	rslt_fp64.f64 *= data_fp32_weight.f32;
}

void __global__ __kernel_add_bias_fp32(void)
{
	data_fp32.f32 += data_fp32_bias.f32;
	rslt_fp64.f64 += data_fp32_bias.f32;
}

/**
 * rslt = rslt * weight + bias
 */
void __global__ __kernel_mul_weight_add_bias_fp64(size_t loop, size_t interval)
{
	for (size_t i = 0; i < loop; i += interval) {
		data_fp64.f64 *= data_fp64_weight.f64;
		data_fp64.f64 += data_fp64_bias.f64;
	}
}

/**
 * rslt = arr[i] * weight[i] + bias[i]
 */
void __global__ __kernel_mul_weight_add_bias_arr_fp64(size_t len,
						      size_t interval)
{
	for (size_t j = 0; j < len; j += interval) {
		data_fp64.f64 +=
			data_fp64_arr[j].f64 * data_fp64_weight_arr[j].f64 +
			data_fp64_bias_arr[j].f64;
	}
}

/**
 * rslt = rslt * weight + bias;
 */
void __global__ __kernel_mul_weight_add_bias_fp32(size_t loop, size_t interval)
{
	for (size_t i = 0; i < loop; i += interval) {
		data_fp32.f32 *= data_fp32_weight.f32;
		data_fp32.f32 += data_fp32_bias.f32;
		rslt_fp64.f64 *= data_fp32_weight.f32;
		rslt_fp64.f64 += data_fp32_bias.f32;
	}
}

/**
 * rslt = rslt * weight;
 */
void __global__ __kernel_mul_weight_fp32(size_t loop, size_t interval)
{
	for (size_t i = 0; i < loop; i += interval) {
		data_fp32.f32 *= data_fp32_weight.f32;
		rslt_fp64.f64 *= data_fp32_weight.f32;
	}
}

/**
 * rslt += a1[i] * a2[i] + bias[i]
 */
void __global__ __kernel_mul_weight_add_bias_arr_fp32(size_t len,
						      size_t interval)
{
	for (size_t j = 0; j < len; j += interval) {
		data_fp32.f32 +=
			data_fp32_arr[j].f32 * data_fp32_weight_arr[j].f32 +
			data_fp32_bias_arr[j].f32;
		rslt_fp64.f64 +=
			data_fp32_arr[j].f32 * data_fp32_weight_arr[j].f32 +
			data_fp32_bias_arr[j].f32;
	}
}

/**
 * rslt += a1[i] * a2[i]
 */
void __global__ __kernel_mul_weight_arr_fp32(size_t len, size_t interval)
{
	for (size_t j = 0; j < len; j += interval) {
		data_fp32.f32 +=
			data_fp32_arr[j].f32 * data_fp32_weight_arr[j].f32;
		rslt_fp64.f64 +=
			data_fp32_arr[j].f32 * data_fp32_weight_arr[j].f32;
	}
}

#ifdef SUPPORT_FP16
/**
 * rslt = rslt * weight
 */
void __global__ __kernel_mul_weight_fp16(size_t loop, size_t interval)
{
	compat_fp16 tmp;

	for (size_t i = 0; i < loop; i += interval) {
		tmp = data_fp16.f16 * data_fp16_weight.f16;

		data_fp16.f16 = tmp;
		rslt_fp32.f32 = compat_half2float(tmp);
	}
}

/**
 * rslt = rslt + bias;
 */
void __global__ __kernel_add_bias_fp16(size_t loop, size_t interval)
{
	compat_fp16 tmp;

	for (size_t i = 0; i < loop; i += interval) {
		tmp = data_fp16.f16 + data_fp16_bias.f16;

		data_fp16.f16 += tmp;
		rslt_fp32.f32 += compat_half2float(tmp);
	}
}

/**
 * rslt = rslt * weight + bias;
 */
void __global__ __kernel_mul_weight_add_bias_fp16(size_t loop, size_t interval)
{
	compat_fp16 tmp;

	for (size_t i = 0; i < loop; i += interval) {
		tmp = data_fp16.f16 * data_fp16_weight.f16 + data_fp16_bias.f16;

		data_fp16.f16 += tmp;
		rslt_fp32.f32 += compat_half2float(tmp);
	}
}

/**
 * rslt += arr[i] * weight[i]
 */
void __global__ __kernel_mul_weight_arr_fp16(size_t len, size_t interval)
{
	compat_fp16 tmp;

	for (size_t j = 0; j < len; j += interval) {
		tmp = data_fp16_arr[j].f16 * data_fp16_weight_arr[j].f16;

		data_fp16.f16 += tmp;
		rslt_fp32.f32 += compat_half2float(tmp);
	}
}

/**
 * rslt += arr[i] + bias[i]
 */
void __global__ __kernel_add_bias_arr_fp16(size_t len, size_t interval)
{
	compat_fp16 tmp;

	for (size_t j = 0; j < len; j += interval) {
		tmp = data_fp16_arr[j].f16 + data_fp16_bias_arr[j].f16;

		data_fp16.f16 += tmp;
		rslt_fp32.f32 += compat_half2float(tmp);
	}
}

/**
 * rslt += arr[i] * weight[i] + bias[i]
 */
void __global__ __kernel_mul_weight_add_bias_arr_fp16(size_t len,
						      size_t interval)
{
	compat_fp16 tmp;

	for (size_t j = 0; j < len; j += interval) {
		tmp = data_fp16_arr[j].f16 * data_fp16_weight_arr[j].f16 +
		      data_fp16_bias_arr[j].f16;

		data_fp16.f16 += tmp;
		rslt_fp32.f32 += compat_half2float(tmp);
	}
}
#endif /* SUPPORT_FP16 */

void overflow_muladd_fp64(void)
{
	for (size_t i = 100; i <= 1000; i += 100) {
		double a = i * 1.123456789f;

		CALL(init_data_fp64, a);

		CALL(__kernel_mul_weight_add_bias_fp64, i, 3);

		seperator();
		TEST("fp64 mul weight and add bias", i);
		check_fp64(st2host(data_fp64, f64));
		reset();
		devSync();
	}
}

void muladd_arr_fp64(void)
{
	for (size_t i = 100; i <= DATA_ARRAY_SIZE; i += 100) {
		CALL(init_data_arr_fp64, i);

		CALL(init_data_fp64, 1);

		CALL(__kernel_mul_weight_add_bias_arr_fp64, i, 1);

		seperator();
		TEST("fp64 mul weight and add bias array", i);
		check_fp32(st2host(data_fp64, f64));
		reset();
		devSync();
	}
}

#if defined(__HPCC__)
# pragma clang diagnostic push
/* warning: reference to __device__ variable 'rslt_fp64' in __host__ function */
# pragma clang diagnostic ignored "-Whpcc-compat"
#elif defined(__LUCA__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wluca-compat"
#endif
void mul_fp32(void)
{
	float a = st2host(fp32_PosMax, f32) / 2.0f;

	stset(data_fp32, fp32_t, f32, a);
	stset(data_fp32_weight, fp32_t, f32, 1.15f);
	stset(data_fp32_bias, fp32_t, f32, 1.15f);
	stset(rslt_fp64, fp64_t, f64, a);

	for (size_t i = 0; i < 10; i++) {
		CALL(__kernel_mul_w_fp32);

		seperator();
		TEST("fp32 mul", i);
		check_fp32(st2host(data_fp32, f32));
		check_fp64(st2host(rslt_fp64, f64));
		reset();
		devSync();
	}
}

void add_fp32(void)
{
	float a = st2host(fp32_PosMax, f32) / 2.0f;
	float weight = st2host(fp32_PosMax, f32) / 9.0f;
	float bias = st2host(fp32_PosMax, f32) / 9.0f;

	stset(data_fp32, fp32_t, f32, a);
	stset(data_fp32_weight, fp32_t, f32, weight);
	stset(data_fp32_bias, fp32_t, f32, bias);
	stset(rslt_fp64, fp64_t, f64, a);

	for (size_t i = 0; i < 10; i++) {
		CALL(__kernel_add_bias_fp32);

		seperator();
		TEST("fp32 add bias", i);
		check_fp32(st2host(data_fp32, f32));
		check_fp64(st2host(rslt_fp64, f64));
		reset();
		devSync();
	}
}

void muladd_fp32(void)
{
	for (size_t i = 100; i <= 1000; i += 100) {
		float a = i * 1.123456789f;

		stset(data_fp32, fp32_t, f32, a);
		stset(data_fp32_weight, fp32_t, f32, 1.000789f);
		stset(data_fp32_bias, fp32_t, f32, 1.000789f);
		stset(rslt_fp64, fp64_t, f64, a);

		CALL(__kernel_mul_weight_fp32, i, 3);

		seperator();
		TEST("fp32 mul weight", i);
		check_fp32(st2host(data_fp32, f32));
		check_fp64(st2host(rslt_fp64, f64));
		reset();
		devSync();
	}

	for (size_t i = 100; i <= 1000; i += 100) {
		float a = i * 1.123456789f;

		stset(data_fp32, fp32_t, f32, a);
		stset(data_fp32_weight, fp32_t, f32, 1.000789f);
		stset(data_fp32_bias, fp32_t, f32, 1.000789f);
		stset(rslt_fp64, fp64_t, f64, a);

		CALL(__kernel_mul_weight_add_bias_fp32, i, 3);

		seperator();
		TEST("fp32 mul weight and add bias", i);
		check_fp32(st2host(data_fp32, f32));
		check_fp64(st2host(rslt_fp64, f64));
		reset();
		devSync();
	}
}

void muladd_arr_fp32(void)
{
	for (size_t i = 100; i <= DATA_ARRAY_SIZE; i += 100) {
		CALL(init_data_arr_fp32, i);

		stset(data_fp32, fp32_t, f32, 1);
		stset(rslt_fp64, fp64_t, f64, 1);

		CALL(__kernel_mul_weight_arr_fp32, i, 1);

		seperator();
		TEST("fp32 mul weight array", i);
		check_fp32(st2host(data_fp32, f32));
		check_fp64(st2host(rslt_fp64, f64));
		reset();
		devSync();
	}

	for (size_t i = 100; i <= DATA_ARRAY_SIZE; i += 100) {
		CALL(init_data_arr_fp32, i);

		stset(data_fp32, fp32_t, f32, 1);
		stset(rslt_fp64, fp64_t, f64, 1);

		CALL(__kernel_mul_weight_add_bias_arr_fp32, i, 1);

		seperator();
		TEST("fp32 mul weight and add bias array", i);
		check_fp32(st2host(data_fp32, f32));
		check_fp64(st2host(rslt_fp64, f64));
		reset();
		devSync();
	}
}

#ifdef SUPPORT_FP16
void muladd_fp16(void)
{
	size_t start, end, interval;

	start = 1;
	end = 10;
	interval = 1;

	seperator();
	/* This value and loop make fp16 almost overflow */
	for (size_t i = 1; i <= 10; i += 1) {
		float fa = 2.7232154321f;
		compat_fp16 a = compat_float2half(fa);

		stset(data_fp16, fp16_t, f16, a);
		stset(data_fp16_weight, fp16_t, f16, a);
		stset(data_fp16_bias, fp16_t, f16, a);
		stset(rslt_fp32, fp32_t, f32, fa);

		CALL(__kernel_mul_weight_fp16, i, 1);

		TEST("fp16 mul weight", i);
		check_fp16(st2host(data_fp16, f16));
		check_fp32(st2host(rslt_fp32, f32));
		devSync();
	}

	seperator();
	for (size_t i = start; i <= end; i += interval) {
		float fa = 1.8432154321f;
		compat_fp16 a = compat_float2half(fa);

		stset(data_fp16, fp16_t, f16, a);
		stset(data_fp16_weight, fp16_t, f16, a);
		stset(data_fp16_bias, fp16_t, f16, a);
		stset(rslt_fp32, fp32_t, f32, fa);

		CALL(__kernel_add_bias_fp16, i, 1);

		TEST("fp16 add bias", i);
		check_fp16(st2host(data_fp16, f16));
		check_fp32(st2host(rslt_fp32, f32));
		devSync();
	}

	seperator();
	for (size_t i = start; i <= end; i += interval) {
		float fa = 1.8432154321f;
		compat_fp16 a = compat_float2half(fa);

		stset(data_fp16, fp16_t, f16, a);
		stset(data_fp16_weight, fp16_t, f16, a);
		stset(data_fp16_bias, fp16_t, f16, a);
		stset(rslt_fp32, fp32_t, f32, fa);

		CALL(__kernel_mul_weight_add_bias_fp16, i, 1);

		TEST("fp16 mul weight and add bias", i);
		check_fp16(st2host(data_fp16, f16));
		check_fp32(st2host(rslt_fp32, f32));
		devSync();
	}
	reset();
}

void muladd_arr_fp16(void)
{
	size_t start, end, interval;

	start = 100;
	end = DATA_ARRAY_SIZE;
	interval = 100;

	seperator();
	for (size_t i = start; i <= end; i += interval) {
		CALL(init_data_arr_fp16, i, 5.5f);

		stset(data_fp16, fp16_t, f16, compat_float2half(1.f));
		stset(rslt_fp32, fp32_t, f32, 1.f);

		CALL(__kernel_mul_weight_arr_fp16, i, 1);

		TEST("fp16 mul weight array", i);
		check_fp16(st2host(data_fp16, f16));
		check_fp32(st2host(rslt_fp32, f32));
		devSync();
	}

	seperator();
	for (size_t i = start; i <= end; i += interval) {
		CALL(init_data_arr_fp16, i, 5.5f);

		stset(data_fp16, fp16_t, f16, compat_float2half(1.f));
		stset(rslt_fp32, fp32_t, f32, 1.f);

		CALL(__kernel_add_bias_arr_fp16, i, 1);

		TEST("fp16 add bias array", i);
		check_fp16(st2host(data_fp16, f16));
		check_fp32(st2host(rslt_fp32, f32));
		devSync();
	}

	seperator();
	for (size_t i = start; i <= end; i += interval) {
		CALL(init_data_arr_fp16, i, 5.5f);

		stset(data_fp16, fp16_t, f16, compat_float2half(1.f));
		stset(rslt_fp32, fp32_t, f32, 1.f);

		CALL(__kernel_mul_weight_add_bias_arr_fp16, i, 1);

		TEST("fp16 mul weight and add bias array", i);
		check_fp16(st2host(data_fp16, f16));
		check_fp32(st2host(rslt_fp32, f32));
		devSync();
	}
	reset();
}
#endif /* SUPPORT_FP16 */

#if defined(__HPCC__) || defined(__LUCA__)
# pragma clang diagnostic pop
#endif

void fp32_overflow_test(void)
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

	reset();
}

void fp64_precision_test(void)
{
	seperator();
	overflow_muladd_fp64();
	seperator();
	muladd_arr_fp64();
	reset();
}

void fp32_precision_test(void)
{
	seperator();
	mul_fp32();
	seperator();
	add_fp32();
	seperator();
	muladd_fp32();
	seperator();
	muladd_arr_fp32();
	reset();
}

void fp16_precision_test(void)
{
#ifdef SUPPORT_FP16
	seperator();
	muladd_fp16();
	seperator();
	muladd_arr_fp16();
	reset();
#endif
}

void precision_tests(void)
{
	if (env.fp64) {
		fp64_precision_test();
	}

	if (env.fp32) {
		fp32_overflow_test();
		fp32_precision_test();
	}

	if (env.fp16) {
		fp16_precision_test();
	}
}

void usage(const char *prog)
{
	fprintf(stderr,
		"\033[m\033[2mUsage: %s [fp64|fp32|fp16|bf16] [version] [nocolor]\033[m\n",
		prog);
}

int main(int argc, char *argv[])
{
	int i;

	assert(sizeof(fp64_t) == 8 && "Bad size of fp64");
	assert(sizeof(fp32_t) == 4 && "Bad size of fp32");
	assert(sizeof(fp16_t) == 2 && "Bad size of fp16");
	assert(sizeof(bf16_t) == 2 && "Bad size of bf16");

	usage(argv[0]);

	for (i = 1; i < argc; i++) {
#define arg_has(v, OP) if (!strncmp(#v, argv[i], strlen(#v))) \
			OP;
		arg_has(nocolor, env.nocolor = true);
		arg_has(version, env.version = true);
		arg_has(fp64, env.fp32 = env.fp16 = env.bf16 = false);
		arg_has(fp32, env.fp64 = env.fp16 = env.bf16 = false);
		arg_has(fp16, env.fp32 = env.fp64 = env.bf16 = false);
		arg_has(bf16, env.fp32 = env.fp64 = env.fp16 = false);
#undef arg_has
	}

	/* always show the version */
	printf("version %s, %s\n", version, DEVICE);
	if (env.version)
		exit(0);

	base_tests();
	precision_tests();

	usage(argv[0]);
	return 0;
}
