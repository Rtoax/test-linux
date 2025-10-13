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

	(void)cudaDeviceSynchronize();
	return 0;
}
