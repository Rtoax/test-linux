// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * TYPES:
 *
 * typedef struct __CUDA_ALIGN__(2) {
 *   unsigned short x;
 * } __half_raw;
 *
 * typedef struct __CUDA_ALIGN__(4) {
 *   unsigned short x;
 *   unsigned short y;
 * } __half2_raw;
 *
 * https://docs.nvidia.com/cuda/cuda-math-api/index.html
 * https://docs.nvidia.com/cuda/cuda-math-api/cuda_math_api/group__CUDA__MATH____HALF__MISC.html
 */
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "cuda_compat.h"
#include "compiler.h"
#include "print.h"

#define USHORT_INF_FP16		0x7C00U
#define USHORT_MAX_NORMAL_FP16	0x7BFFU
#define USHORT_MIN_DENORM_FP16	0x0001U
#define USHORT_NAN_FP16		0x7FFFU
#define USHORT_NEG_ZERO_FP16	0x8000U
#define USHORT_ZERO_FP16	0x0000U
#define USHORT_ONE_FP16		0x3C00U

#ifndef __NVCC__
/**
 * Half Arithmetic Constants
 * https://docs.nvidia.com/cuda/cuda-math-api/cuda_math_api/group__CUDA__MATH__INTRINSIC__HALF__PHALFS.html
 */
#define CUDART_INF_FP16 __ushort_as_half((unsigned short)USHORT_INF_FP16)
#define CUDART_MAX_NORMAL_FP16 __ushort_as_half((unsigned short)USHORT_MAX_NORMAL_FP16)
#define CUDART_MIN_DENORM_FP16 __ushort_as_half((unsigned short)USHORT_MIN_DENORM_FP16)
#define CUDART_NAN_FP16 __ushort_as_half((unsigned short)USHORT_NAN_FP16)
#define CUDART_NEG_ZERO_FP16 __ushort_as_half((unsigned short)USHORT_NEG_ZERO_FP16)
#define CUDART_ZERO_FP16 __ushort_as_half((unsigned short)USHORT_ZERO_FP16)
#define CUDART_ONE_FP16 __ushort_as_half((unsigned short)USHORT_ONE_FP16)
#endif

__global__ void k_types(void)
{
	__half_raw hraw = { .x = USHORT_ONE_FP16, };
	__half2_raw h2raw = { .x = USHORT_ONE_FP16, .y = USHORT_ONE_FP16, };

	PHALFRAW(hraw);
	PHALF2RAW(h2raw);
}

__global__ void k_half_constants(void)
{
	PHALF(CUDART_INF_FP16);
	PHALF(CUDART_INF_FP16);
	PHALF(CUDART_MAX_NORMAL_FP16);
	PHALF(CUDART_MIN_DENORM_FP16);
	PHALF(CUDART_NAN_FP16);
	PHALF(CUDART_NEG_ZERO_FP16);
	PHALF(CUDART_ZERO_FP16);
	PHALF(CUDART_ONE_FP16);
}

__global__ void k_half_arithmetic(void)
{
	half h1, h2, h3;

	h1 = __float2half(1);
	h2 = __float2half(2);
	h3 = __float2half(3);

	PHALF(h1);
	PHALF(h2);
	PHALF(h3);

	PHALF(__habs(h1));
	PHALF(__hadd(h1, h2));
	PHALF((h1 + h2));
#if !defined(__HIPCC__)
	PHALF(__hadd_rn(h1, h2));
#endif
	PHALF(__hdiv(h1, h2));
	PHALF((h1 / h2));
	PHALF(__hfma(h1, h2, h3));	/* (a x b) + c */
#if !defined(__HIPCC__)
	PHALF(__hfma_relu(h1, h2, h3));
#endif
	PHALF(__hfma_sat(h1, h2, h3));
	PHALF(__hmul(h1, h2));
	PHALF((h1 * h2));
#if !defined(__HIPCC__)
	PHALF(__hmul_rn(h1, h2));
#endif
	PHALF(__hmul_sat(h1, h2));
	PHALF(__hneg(h1));
	PHALF(__hsub(h1, h2));
#if !defined(__HIPCC__)
	PHALF(__hsub_rn(h1, h2));
#endif
	PHALF(__hsub_sat(h1, h2));
}

/**
 * FIXME: HIP don't have atomicAdd() of half type?
 */
#if !defined(__HIPCC__)
__global__ void k_half_arithmetic_atomicAdd(void)
{
	extern __shared__ half shareHalf[];

	shareHalf[0] = CUDART_ONE_FP16;

	__syncthreads();

	atomicAdd(shareHalf, CUDART_ONE_FP16);

	__syncthreads();

	if (threadIdx.x + blockDim.x * blockIdx.x == 0) {
		PHALF(shareHalf[0]);
	}
}
#endif

__global__ void k_half_comparision(void)
{
	half h1, h2, h3;

	h1 = __float2half(1);
	h2 = __float2half(2);
	h3 = __float2half(3);

	PHALF(h1);
	PHALF(h2);
	PHALF(h3);

	PBOOL(__heq(h1, h2));
	PBOOL(__heq(h1, h1));
	PBOOL(__hequ(h1, h1));
	PBOOL(__hequ(h1, h2));
	PBOOL(__hge(h1, h2));
	PBOOL(__hgeu(h1, h2));
	PBOOL(__hgt(h1, h2));
	PBOOL(__hgtu(h1, h2));
	PBOOL(__hle(h1, h2));
	PBOOL(__hleu(h1, h2));
	PBOOL(__hlt(h1, h2));
	PBOOL(__hltu(h1, h2));
	PBOOL(__hne(h1, h2));
	PBOOL(__hneu(h1, h2));
	PBOOL(__hisinf(h1));
	PBOOL(__hisinf(CUDART_INF_FP16));
	PBOOL(__hisnan(h1));
	PBOOL(__hisnan(CUDART_NAN_FP16));

	PHALF(__hmax(h1, h2));
	PHALF(__hmax_nan(h1, h2));
	PHALF(__hmin(h1, h2));
	PHALF(__hmin_nan(h1, h2));
}

__global__ void k_half_math(void)
{
	half f16 = __float2half(3.14);

	PHALF(hceil(f16));
	PHALF(hfloor(f16));
	PHALF(hcos(f16));
	PHALF(hsin(f16));
#if !defined(__HPCC__) && !defined(__HIPCC__) && CUDA_VERSION >= 13000
	PHALF(htanh(f16));
	PHALF(htanh_approx(f16));
#endif
	PHALF(hexp(f16));
	PHALF(hexp2(f16));
	PHALF(hexp10(f16));
	PHALF(hlog(f16));
	PHALF(hlog2(f16));
	PHALF(hlog10(f16));
	PHALF(hrcp(f16));
	PHALF(hrint(f16));
	PHALF(hsqrt(f16));
	PHALF(hrsqrt(f16));
	PHALF(htrunc(f16));
}

__global__ void k_half_precision_conversion(void)
{
	double __unused d;
	float __unused f;
	half h;
	half2 h2;
	float2 f2; /* float2: {x, y} */
	signed char __unused sc;
	unsigned char __unused uc;
	short int __unused si;
	unsigned short int __unused usi;
	int __unused i;
	unsigned int __unused ui;
	long long int __unused ll;
	unsigned long long int __unused ull;

	PHALF((h = __int2half_rd(3)));
	PHALF((h = __int2half_rn(3)));
	PHALF((h = __int2half_ru(3)));
	PHALF((h = __int2half_rz(3)));
#if !defined(__HIPCC__)
	PHALF((h = __double2half(3.1415926)));
#endif
	PHALF((h = __float2half(3.1415926f)));
	PFLOAT((f = __half2float(h)));
	PHALF2((h2 = __half2half2(h)));
	PHALF2((h2 = make_half2(h, h)));
	PHALF2((h2 = __halves2half2(h, h)));
	PFLOAT((f = __low2float(h2)));
	PHALF((h = __low2half(h2)));
	PHALF2((h2 = __low2half2(h2)));
	PHALF2((h2 = __lows2half2(h2, h2)));
	PHALF2((h2 = __lowhigh2highlow(h2)));
	PHALF((h = __ll2half_rd(314159L)));
	PHALF((h = __ll2half_rn(314159L)));
	PHALF((h = __ll2half_ru(314159L)));
	PHALF((h = __ll2half_rz(314159L)));
	PLONGLONG((ll = __half2ll_rd(h)));
	PLONGLONG((ll = __half2ll_rn(h)));
	PLONGLONG((ll = __half2ll_ru(h)));
	PLONGLONG((ll = __half2ll_rz(h)));
	PLONGLONG((ull = __half2ull_rd(h)));
	PLONGLONG((ull = __half2ull_rn(h)));
	PLONGLONG((ull = __half2ull_ru(h)));
	PLONGLONG((ull = __half2ull_rz(h)));
	PHALF((h = __ull2half_rd(ull)));
	PHALF((h = __ull2half_rn(ull)));
	PHALF((h = __ull2half_ru(ull)));
	PHALF((h = __ull2half_rz(ull)));
	PSHORT((si = __half2short_rd(h)));
	PSHORT((si = __half2short_rn(h)));
	PSHORT((si = __half2short_ru(h)));
	PSHORT((si = __half2short_rz(h)));
	PSHORT((si = __half_as_short(h)));
	PHALF((h = __short2half_rd(si)));
	PHALF((h = __short2half_rn(si)));
	PHALF((h = __short2half_ru(si)));
	PHALF((h = __short2half_rz(si)));
	PSHORT((usi = __half2ushort_rd(h)));
	PSHORT((usi = __half2ushort_rn(h)));
	PSHORT((usi = __half2ushort_ru(h)));
	PSHORT((usi = __half2ushort_rz(h)));
	PSHORT((usi = __half_as_ushort(h)));
	PHALF((h = __ushort2half_rd(usi)));
	PHALF((h = __ushort2half_rn(usi)));
	PHALF((h = __ushort2half_ru(usi)));
	PHALF((h = __ushort2half_rz(usi)));
	PHALF((h = __ushort_as_half(usi)));
	PINT((i = __half2int_rd(h))); /* round-down */
	PINT((i = __half2int_rn(h))); /* round-to-nearest-even */
	PINT((i = __half2int_ru(h))); /* round-up */
	PINT((i = __half2int_rz(h))); /* round-zero */
	PINT((ui = __half2uint_rd(h)));
	PINT((ui = __half2uint_rn(h)));
	PINT((ui = __half2uint_ru(h)));
	PINT((ui = __half2uint_rz(h)));
	PHALF((h = __uint2half_rd(ui)));
	PHALF((h = __uint2half_rn(ui)));
	PHALF((h = __uint2half_ru(ui)));
	PHALF((h = __uint2half_rz(ui)));

	PHALF(__float2half_rn(3.1415926f)); /* round-to-nearest-even */
	PHALF(__float2half_ru(3.1415926f)); /* round-up */
	PHALF(__float2half_rd(3.1415926f)); /* round-down */
	PHALF(__float2half_rz(3.1415926f)); /* round-zero */
	PHALF2(__float2half2_rn(3.1415926f)); /* round-to-nearest-even */

	PHALF2((h2 = __floats2half2_rn(3.1415926f, 3.1415926f))); /* round-to-nearest-even */
	PFLOAT((f = __high2float(h2)))
	PHALF((h = __high2half(h2)));
	PHALF2((h2 = __high2half2(h2)));
	PHALF2((h2 = __highs2half2(h2, h2)));
	PFLOAT2((f2 = __half22float2(h2)));
	PHALF2(__float22half2_rn(f2));

#if !defined(__HPCC__) && !defined(__HIPCC__)
	PCHAR((sc = __half2char_rz(3.1415926f)));
	PCHAR((uc = __half2uchar_rz(3.1415926f)));
#endif

	PHALF((h = __ldca(&h))); /* Generates a ld.global.ca load instruction */
	PHALF2((h2 = __ldca(&h2)));
	PHALF((h = __ldcg(&h))); /* Generates a ld.global.cg load instruction. */
	PHALF2((h2 = __ldcg(&h2)));
	PHALF((h = __ldcs(&h))); /* ld.global.cv */
	PHALF2((h2 = __ldcs(&h2)));
#if !defined(__HIPCC__)
	PHALF((h = __ldcv(&h))); /* ld.global.cv */
	PHALF2((h2 = __ldcv(&h2)));
	PHALF((h = __ldlu(&h))); /* ld.global.lu */
	PHALF2((h2 = __ldlu(&h2)));
#endif
	PHALF((h = __ldg(&h))); /* ld.global.nc */
	PHALF2((h2 = __ldg(&h2)));

#if !defined(__HIPCC__)
	/* st.global.cg */
	__stcg(&h, h);
	__stcg(&h2, h2);
	/* st.global.cs */
	__stcs(&h, h);
	__stcs(&h2, h2);
	/* st.global.wb */
	__stwb(&h, h);
	__stwb(&h2, h2);
	/* st.global.wt */
	__stwt(&h, h);
	__stwt(&h2, h2);
#endif
}

__global__ void k_half_precision_conversion_sync(void)
{
	/**
	 * __shfl_down_sync
	 * __shfl_sync
	 * __shfl_up_sync
	 * __shfl_xor_sync
	 */
}

__global__ void k_half2_arithmetic(void)
{
	half h;
	half2 h2_1, h2_2, h2_3;

	PHALF((h = __float2half(3.1415926f)));
	PHALF2((h2_1 = __half2half2(h)));
	PHALF2((h2_2 = __half2half2(h)));
	PHALF2((h2_3 = __half2half2(h)));

	PHALF2(__h2div(h2_1, h2_2));
	PHALF2((h2_1 / h2_2));
	PHALF2(__habs2(h2_1));
	PHALF2(__hadd2(h2_1, h2_2));
	PHALF2((h2_1 + h2_2));
#if !defined(__HIPCC__)
	PHALF2(__hadd2_rn(h2_1, h2_2)); /* rn: round-to-nearest-even */
#endif
	PHALF2(__hadd2_sat(h2_1, h2_2)); /* round-to-nearest-even mode, with saturation to [0.0, 1.0]. */
#if !defined(__HIPCC__)
	PHALF2(__hcmadd(h2_1, h2_2, h2_3));
#endif
	PHALF2(__hfma2(h2_1, h2_2, h2_3));
#if !defined(__HIPCC__)
	PHALF2(__hfma2_relu(h2_1, h2_2, h2_3));
#endif
	PHALF2(__hfma2_sat(h2_1, h2_2, h2_3));
	PHALF2(__hmul2(h2_1, h2_2));
	PHALF2((h2_1 * h2_2));
#if !defined(__HIPCC__)
	PHALF2(__hmul2_rn(h2_1, h2_2));
#endif
	PHALF2(__hmul2_sat(h2_1, h2_2));
	PHALF2(__hneg2(h2_1));
	PHALF2(__hsub2(h2_1, h2_2));
#if !defined(__HIPCC__)
	PHALF2(__hsub2_rn(h2_1, h2_2));
#endif
	PHALF2(__hsub2_sat(h2_1, h2_2));
}

#if !defined(__HIPCC__)
__global__ void k_half2_arithmetic_atomicAdd(void)
{
	extern __shared__ half2 shareHalf2[];
	half h;
	half2 h2;

	h = __float2half(3.1415926f);
	h2 = __half2half2(h);
	shareHalf2[0] = h2;

	__syncthreads();

	atomicAdd(shareHalf2, h2);

	__syncthreads();

	if (threadIdx.x + blockDim.x * blockIdx.x == 0) {
		PHALF2(h2);
		PHALF2(shareHalf2[0]);
	}
}
#endif

__global__ void k_half2_comparision(void)
{
	half h_1, h_2, h_3;
	half2 h2_1, h2_2, h2_3, h2_nan;

	PHALF((h_1 = __float2half(1)));
	PHALF((h_2 = __float2half(2)));
	PHALF((h_3 = __float2half(3)));

	PHALF2((h2_1 = __half2half2(h_1)));
	PHALF2((h2_2 = __half2half2(h_2)));
	PHALF2((h2_3 = __half2half2(h_3)));
	PHALF2((h2_nan = __half2half2(CUDART_NAN_FP16)));

	PBOOL(__hbeq2(h2_1, h2_1)); /* if-equal comparison */
	PBOOL(__hbeq2(h2_1, h2_2));
	PBOOL(__hbequ2(h2_1, h2_1)); /* unordered if-equal comparison */
	PBOOL(__hbequ2(h2_1, h2_2));
	PBOOL(__hbge2(h2_1, h2_2));
	PBOOL(__hbgeu2(h2_2, h2_1));
	PBOOL(__hbgt2(h2_1, h2_2));
	PBOOL(__hbgtu2(h2_2, h2_1));
	PBOOL(__hble2(h2_1, h2_2));
	PBOOL(__hbleu2(h2_2, h2_1));
	PBOOL(__hblt2(h2_1, h2_2));
	PBOOL(__hbltu2(h2_2, h2_1));
	PBOOL(__hbne2(h2_1, h2_2));
	PBOOL(__hbneu2(h2_2, h2_1));

	PHALF2(__heq2(h2_1, h2_1));
	PHALF2(__heq2(h2_1, h2_2));
#if !defined(__HPCC__) && !defined(__HIPCC__)
	PINT(__heq2_mask(h2_1, h2_1));
	PINT(__heq2_mask(h2_1, h2_2));
#endif
	PHALF2(__hequ2(h2_1, h2_1));
#if !defined(__HPCC__) && !defined(__HIPCC__)
	PINT(__hequ2_mask(h2_1, h2_1));
#endif
	PHALF2(__hge2(h2_1, h2_1));
#if !defined(__HPCC__) && !defined(__HIPCC__)
	PINT(__hge2_mask(h2_1, h2_1));
#endif
	PHALF2(__hgeu2(h2_1, h2_1));
#if !defined(__HPCC__) && !defined(__HIPCC__)
	PINT(__hgeu2_mask(h2_1, h2_1));
#endif
	PHALF2(__hgt2(h2_1, h2_1));
#if !defined(__HPCC__) && !defined(__HIPCC__)
	PINT(__hgt2_mask(h2_1, h2_1));
#endif
	PHALF2(__hgtu2(h2_1, h2_1));
#if !defined(__HPCC__) && !defined(__HIPCC__)
	PINT(__hgtu2_mask(h2_1, h2_1));
#endif
	PHALF2(__hle2(h2_1, h2_1));
#if !defined(__HPCC__) && !defined(__HIPCC__)
	PINT(__hle2_mask(h2_1, h2_1));
#endif
	PHALF2(__hleu2(h2_1, h2_1));
#if !defined(__HPCC__) && !defined(__HIPCC__)
	PINT(__hleu2_mask(h2_1, h2_1));
#endif
	PHALF2(__hlt2(h2_1, h2_1));
#if !defined(__HPCC__) && !defined(__HIPCC__)
	PINT(__hlt2_mask(h2_1, h2_1));
#endif
	PHALF2(__hltu2(h2_1, h2_1));
#if !defined(__HPCC__) && !defined(__HIPCC__)
	PINT(__hltu2_mask(h2_1, h2_1));
#endif
	PHALF2(__hne2(h2_1, h2_1));
#if !defined(__HPCC__) && !defined(__HIPCC__)
	PINT(__hne2_mask(h2_1, h2_1));
#endif
	PHALF2(__hneu2(h2_1, h2_1));
#if !defined(__HPCC__) && !defined(__HIPCC__)
	PINT(__hneu2_mask(h2_1, h2_1));
#endif

	PHALF2(__hisnan2(h2_1));
	PHALF2(__hisnan2(h2_nan));

#if !defined(__HIPCC__)
	PHALF2(__hmax2(h2_1, h2_2));
	PHALF2(__hmax2(h2_1, h2_nan));
	PHALF2(__hmax2_nan(h2_1, h2_nan));
	PHALF2(__hmin2(h2_1, h2_2));
	PHALF2(__hmin2(h2_1, h2_nan));
	PHALF2(__hmin2_nan(h2_1, h2_nan));
#endif
}

__global__ void k_half2_math(void)
{
	half2 h2_pi;

	PHALF2((h2_pi = __half2half2(__float2half(3.1415926f))));

	PHALF2(h2ceil(h2_pi));
	PHALF2(h2floor(h2_pi));
	PHALF2(h2cos(h2_pi));
	PHALF2(h2sin(h2_pi));
#if !defined(__HPCC__) && !defined(__HIPCC__) && CUDA_VERSION >= 13000
	PHALF2(h2tanh(h2_pi));
	PHALF2(h2tanh_approx(h2_pi)); /* approximate hyperbolic tangent */
#endif
	PHALF2(h2exp(h2_pi));
	PHALF2(h2exp10(h2_pi));
	PHALF2(h2exp2(h2_pi));
	PHALF2(h2log(h2_pi));
	PHALF2(h2log10(h2_pi));
	PHALF2(h2log2(h2_pi));
	PHALF2(h2rcp(h2_pi)); /* reciprocal */
	PHALF2(h2rint(h2_pi)); /* nearest integer value */
	PHALF2(h2sqrt(h2_pi));
	PHALF2(h2rsqrt(h2_pi)); /* reciprocal square root */
	PHALF2(h2trunc(h2_pi));
}

int main(int argc, char *argv[])
{
	dim3 grid(10);
	dim3 block(32);

	assert(sizeof(half) == 2 && "bad size of half");
	assert(sizeof(__half_raw) == 2 && "bad size of __half_raw");
	assert(sizeof(half2) == 4 && "bad size of half2");
	assert(sizeof(__half2_raw) == 4 && "bad size of __half2_raw");
	assert(sizeof(float2) == 8 && "bad size of float2");

	k_types<<<1, 1>>>();

	k_half_constants<<<1, 1>>>();
	k_half_arithmetic<<<1, 1>>>();
#if !defined(__HIPCC__)
	(void)cudaLaunchKernel((void *)k_half_arithmetic_atomicAdd, grid, block, NULL,
				sizeof(half), NULL);
#endif
	k_half_comparision<<<1, 1>>>();
	k_half_math<<<1, 1>>>();
	k_half_precision_conversion<<<1, 1>>>();
	k_half_precision_conversion_sync<<<1, 1>>>();

	k_half2_arithmetic<<<1, 1>>>();

#if !defined(__HIPCC__)
	(void)cudaLaunchKernel((void *)k_half2_arithmetic_atomicAdd, grid, block, NULL,
				sizeof(half2), NULL);
#endif
	k_half2_comparision<<<1, 1>>>();
	k_half2_math<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
