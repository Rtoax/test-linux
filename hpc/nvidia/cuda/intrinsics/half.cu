// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "cuda_compat.h"


#ifndef __NVCC__
/**
 * Half Arithmetic Constants
 * https://docs.nvidia.com/cuda/cuda-math-api/cuda_math_api/group__CUDA__MATH__INTRINSIC__HALF__PHALFS.html
 */
#define CUDART_INF_FP16 __ushort_as_half((unsigned short)0x7C00U)
#define CUDART_MAX_NORMAL_FP16 __ushort_as_half((unsigned short)0x7BFFU)
#define CUDART_MIN_DENORM_FP16 __ushort_as_half((unsigned short)0x0001U)
#define CUDART_NAN_FP16 __ushort_as_half((unsigned short)0x7FFFU)
#define CUDART_NEG_ZERO_FP16 __ushort_as_half((unsigned short)0x8000U)
#define CUDART_ZERO_FP16 __ushort_as_half((unsigned short)0x0000U)
#define CUDART_ONE_FP16 __ushort_as_half((unsigned short)0x3C00U)
#endif

/* Print definitions */
#define PHALF(v)	printf("%s : %f\n", #v, __half2float(v));


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

	h1 = __float2half(3.14);
	h2 = __float2half(3.14);

	h3 = __hmul(h1, h2);
	PHALF(h3);
}

__global__ void k_half_math(void)
{
	half f16 = __float2half(3.14);

	PHALF(hceil(f16));
	PHALF(hfloor(f16));
	PHALF(hcos(f16));
	PHALF(hsin(f16));
/* FIXME: hpcc don't have them */
#if !defined(__HPCC__) && !defined(__HIPCC__)
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

int main(int argc, char *argv[])
{
	k_half_constants<<<1, 1>>>();
	k_half_arithmetic<<<1, 1>>>();
	k_half_math<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
