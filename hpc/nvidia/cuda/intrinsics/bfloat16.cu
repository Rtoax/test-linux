// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * https://docs.nvidia.com/cuda/cuda-math-api/index.html
 * https://docs.nvidia.com/cuda/cuda-math-api/cuda_math_api/group__CUDA__MATH__INTRINSIC__BFLOAT16.html
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

/**
 * Bfloat16 Arithmetic Constants
 * https://docs.nvidia.com/cuda/cuda-math-api/cuda_math_api/group__CUDA__MATH__INTRINSIC__BFLOAT16__CONSTANTS.html
 */
#ifndef __NVCC__
#define CUDART_INF_BF16	__ushort_as_bfloat16((unsigned short)0x7F80U)
#define CUDART_MAX_NORMAL_BF16	__ushort_as_bfloat16((unsigned short)0x7F7FU)
#define CUDART_MIN_DENORM_BF16	__ushort_as_bfloat16((unsigned short)0x0001U)
#define CUDART_NAN_BF16	__ushort_as_bfloat16((unsigned short)0x7FFFU)
#define CUDART_NEG_ZERO_BF16	__ushort_as_bfloat16((unsigned short)0x8000U)
#define CUDART_ONE_BF16	__ushort_as_bfloat16((unsigned short)0x3F80U)
#define CUDART_ZERO_BF16	__ushort_as_bfloat16((unsigned short)0x0000U)
#endif

__global__ void k_bfloat16_constants(void)
{
	PBF16(CUDART_INF_BF16);
	PBF16(CUDART_MAX_NORMAL_BF16);
	PBF16(CUDART_MIN_DENORM_BF16);
	PBF16(CUDART_NAN_BF16);
	PBF16(CUDART_NEG_ZERO_BF16);
	PBF16(CUDART_ONE_BF16);
	PBF16(CUDART_ZERO_BF16);
}

__global__ void k_bfloat16_arithmetic(void)
{
	__nv_bfloat16 one = __float2bfloat16(1);
	__nv_bfloat16 neg_one = __float2bfloat16(-1);
	__nv_bfloat16 two = __float2bfloat16(2);
	__nv_bfloat16 three = __float2bfloat16(3);
	__nv_bfloat16 pi = __float2bfloat16(3.141592653f);
	__nv_bfloat16 neg_pi = __float2bfloat16(-3.141592653f);
	__nv_bfloat16 tmp = one;

	PBF16(one);
	PBF16(neg_one);
	PBF16(pi);
	PBF16(neg_pi);

	PBF16(__habs(neg_one));
	PBF16(__hadd(one, pi));
	PBF16((two + pi));
#if !defined(__HIPCC__)
	PBF16(__hadd_rn(one, pi)); /* round-to-nearest-even */
	PBF16(__hadd_sat(one, pi)); /* round-to-nearest-even mode, with saturation to [0.0, 1.0] */
#endif
	PBF16(__hdiv(one, pi));
	PBF16((one / pi));
	PBF16((tmp /= pi));
	/* FMA: x * y + z */
	PBF16(__hfma(one, two, three)); /* fused multiply-add in round-to-nearest-even mode */
#if !defined(__HIPCC__)
	PBF16(__hfma_relu(one, two, three));
	PBF16(__hfma_sat(one, two, three));
#endif
	PBF16(__hmul(one, pi));
	PBF16((two * pi));
	PBF16((tmp *= pi));
#if !defined(__HIPCC__)
	PBF16(__hmul_rn(one, pi));
	PBF16(__hmul_sat(one, pi));
#endif
	PBF16(__hneg(one));
	PBF16(__hsub(two, one));
	PBF16((two - one));
	PBF16((tmp -= one));
#if !defined(__HIPCC__)
	PBF16(__hsub_rn(two, one));
	PBF16(__hsub_sat(two, one));
#endif
}

#if !defined(__HIPCC__)
__global__ void k_bfloat16_arithmetic_atomicAdd(void)
{
	extern __shared__ __nv_bfloat16 shareBfloat16[1];

	__syncthreads();

	atomicAdd(shareBfloat16, CUDART_ONE_BF16);

	__syncthreads();

	if (threadIdx.x + blockDim.x * blockIdx.x == 0) {
		PBF16(shareBfloat16[0]);
	}
}
#endif

__global__ void k_bfloat16_comparision(void)
{
	__nv_bfloat16 one = __float2bfloat16(1);
	__nv_bfloat16 two = __float2bfloat16(2);
	__nv_bfloat16 three = __float2bfloat16(3);
	__nv_bfloat16 pi = __float2bfloat16(3.141592653f);

	PBOOL(__heq(one, one));
	PBOOL((one == one));
	PBOOL(__hequ(one, one)); /* unordered */
	PBOOL(__hge(one, one));
	PBOOL((one >= one));
	PBOOL(__hgeu(one, one));
	PBOOL(__hgt(one, one));
	PBOOL((one > one));
	PBOOL(__hgtu(one, one));
	PBOOL(__hle(one, one));
	PBOOL((one <= one));
	PBOOL(__hleu(one, one));
	PBOOL(__hlt(one, one));
	PBOOL((one < one));
	PBOOL(__hltu(one, one));
	PBOOL(__hne(one, one));
	PBOOL((one != one));
	PBOOL(__hneu(one, one));
	PBOOL(__hmax(one, two));
#if !defined(__HIPCC__)
	PBOOL(__hmax_nan(one, two));
#endif
	PBOOL(__hmin(one, two));
#if !defined(__HIPCC__)
	PBOOL(__hmin_nan(one, two));
#endif
	PBOOL(__hisinf(CUDART_INF_BF16)); /* is infinite */
	PBOOL(__hisnan(CUDART_NAN_BF16));
}

__global__ void k_bfloat16_math(void)
{
	__nv_bfloat16 pi = __float2bfloat16(3.141592653f);

	PBF16(hceil(pi));
	PBF16(hfloor(pi));
	PBF16(hcos(pi));
	PBF16(hsin(pi));
#if !defined(__HPCC__) && !defined(__HIPCC__) && CUDA_VERSION >= 13000
	PBF16(htanh(pi));
	PBF16(htanh_approx(pi));
#endif
	PBF16(hexp(pi));
	PBF16(hexp2(pi));
	PBF16(hexp10(pi));
	PBF16(hlog(pi));
	PBF16(hlog2(pi));
	PBF16(hlog10(pi));
	PBF16(hrcp(pi));
	PBF16(hrint(pi));
	PBF16(hsqrt(pi));
	PBF16(hrsqrt(pi));
	PBF16(htrunc(pi));
}

__global__ void k_bfloat16_precision_conversion(void)
{
	const __nv_bfloat16 one = __float2bfloat16(1);
	const __nv_bfloat16 two = __float2bfloat16(2);
	const __nv_bfloat16 three = __float2bfloat16(3);
	const __nv_bfloat16 A = __float2bfloat16('A');
	const __nv_bfloat16 pi = __float2bfloat16(3.141592653f);

	__nv_bfloat16 bf16;
	__nv_bfloat162 bf162;
	float2 f2;

	PBF162((bf162 = __bfloat162bfloat162(pi)));
	PFLOAT2((f2 = __bfloat1622float2(bf162)));
#if !defined(__HPCC__) && !defined(__HIPCC__)
	PCHAR(__bfloat162char_rz(A));
	PCHAR(__bfloat162uchar_rz(A));
#endif

	PFLOAT(__bfloat162float(pi));

#if !defined(__HIPCC__)
	PINT(__bfloat162int_rd(pi))
	PINT(__bfloat162int_rn(pi))
	PINT(__bfloat162int_ru(pi))
	PINT(__bfloat162int_rz(pi))
	PINT(__bfloat162uint_rd(pi))
	PINT(__bfloat162uint_rn(pi))
	PINT(__bfloat162uint_ru(pi))
	PINT(__bfloat162uint_rz(pi))
#endif

#if !defined(__HIPCC__)
	PLONGLONG(__bfloat162ll_rd(pi));
	PLONGLONG(__bfloat162ll_rn(pi));
	PLONGLONG(__bfloat162ll_ru(pi));
	PLONGLONG(__bfloat162ll_rz(pi));
	PLONGLONG(__bfloat162ull_rd(pi));
	PLONGLONG(__bfloat162ull_rn(pi));
	PLONGLONG(__bfloat162ull_ru(pi));
	PLONGLONG(__bfloat162ull_rz(pi));
#endif

#if !defined(__HIPCC__)
	PSHORT(__bfloat162short_rd(pi));
	PSHORT(__bfloat162short_rn(pi));
	PSHORT(__bfloat162short_ru(pi));
	PSHORT(__bfloat162short_rz(pi));
	PSHORT(__bfloat162ushort_rd(pi));
	PSHORT(__bfloat162ushort_rn(pi));
	PSHORT(__bfloat162ushort_ru(pi));
	PSHORT(__bfloat162ushort_rz(pi));
#endif

	PSHORT(__bfloat16_as_short(pi));
	PSHORT(__bfloat16_as_ushort(pi));

	PBF16(__double2bfloat16(3.14));
	PBF16(__float2bfloat16(3.14f));
#if !defined(__HIPCC__)
	PBF16(__float2bfloat16_rd(3.14f));
	PBF16(__float2bfloat16_rn(3.14f));
	PBF16(__float2bfloat16_ru(3.14f));
	PBF16(__float2bfloat16_rz(3.14f));
#endif
	PBF16(__high2bfloat16(bf162));
	PBF16(__low2bfloat16(bf162));

	PBF162(__float22bfloat162_rn(f2));
#if !defined(__HIPCC__)
	PBF162(__float2bfloat162_rn(3.14f));
	PBF162((bf162 = __floats2bfloat162_rn(3.14f, 1.23f)));
#endif
	PBF162(__halves2bfloat162(one, pi));

	PBF162(__high2bfloat162(bf162));
	PBF162(__low2bfloat162(bf162));
	PBF162(__highs2bfloat162(bf162, bf162));
	PBF162(__lows2bfloat162(bf162, bf162));

	PBF162(__lowhigh2highlow(bf162));

	PFLOAT(__high2float(bf162));
	PFLOAT(__low2float(bf162));

#if !defined(__HIPCC__)
	PBF16(__int2bfloat16_rd(1)); /* round-down */
	PBF16(__int2bfloat16_rn(1)); /* round-to-nearest-even */
	PBF16(__int2bfloat16_ru(1)); /* round-up */
	PBF16(__int2bfloat16_rz(1)); /* round-towards-zero */
#endif

	/**
	 * FIXME: on HPCC 3.0.0 running error, just skip it right now, see:
	 * commit 15831f87320e ("bfloat16.cu: test ld.global.{ca,cg,cs,cv,nc,lu}")
	 */
#if !defined(__HPCC__)
	PBF162(__ldca(&bf162));
	PBF16((bf16 = __ldca(&pi)));
	PBF162(__ldcg(&bf162));
	PBF16((bf16 = __ldcg(&pi)));
	PBF162(__ldcs(&bf162));
	PBF16((bf16 = __ldcs(&pi)));
	PBF162(__ldcv(&bf162));
	PBF16((bf16 = __ldcv(&pi)));
	PBF162(__ldg(&bf162));
	PBF16((bf16 = __ldg(&pi)));
	PBF162(__ldlu(&bf162));
	PBF16((bf16 = __ldlu(&pi)));
#endif

	PBF16(__ll2bfloat16_rd(3UL));
	PBF16(__ll2bfloat16_rn(3UL));
	PBF16(__ll2bfloat16_ru(3UL));
	PBF16(__ll2bfloat16_rz(3UL));
}

int main(int argc, char *argv[])
{
	dim3 grid1(1), grid(10);
	dim3 block1(1), block(32);

	assert(sizeof(__nv_bfloat16) == 2 && "bad size of half");

	k_bfloat16_constants<<<1, 1>>>();
	k_bfloat16_arithmetic<<<1, 1>>>();
#if !defined(__HIPCC__)
	(void)cudaLaunchKernel((void *)k_bfloat16_arithmetic_atomicAdd, grid, block, NULL,
				sizeof(__nv_bfloat16), NULL);
#endif
	k_bfloat16_comparision<<<1, 1>>>();
	k_bfloat16_math<<<1, 1>>>();
	k_bfloat16_precision_conversion<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
