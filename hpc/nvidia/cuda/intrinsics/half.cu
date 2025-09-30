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
 * https://docs.nvidia.com/cuda/cuda-math-api/cuda_math_api/group__CUDA__MATH__INTRINSIC__HALF__CONSTANTS.html
 */
#define CUDART_INF_FP16 __ushort_as_half((unsigned short)0x7C00U)
#define CUDART_MAX_NORMAL_FP16 __ushort_as_half((unsigned short)0x7BFFU)
#define CUDART_MIN_DENORM_FP16 __ushort_as_half((unsigned short)0x0001U)
#define CUDART_NAN_FP16 __ushort_as_half((unsigned short)0x7FFFU)
#define CUDART_NEG_ZERO_FP16 __ushort_as_half((unsigned short)0x8000U)
#define CUDART_ZERO_FP16 __ushort_as_half((unsigned short)0x0000U)
#define CUDART_ONE_FP16 __ushort_as_half((unsigned short)0x3C00U)
#endif

__global__ void k_half_constants(void)
{
#define CONSTANT(v)	printf("%s : %f\n", #v, __half2float(v));
	CONSTANT(CUDART_INF_FP16);
	CONSTANT(CUDART_INF_FP16);
	CONSTANT(CUDART_MAX_NORMAL_FP16);
	CONSTANT(CUDART_MIN_DENORM_FP16);
	CONSTANT(CUDART_NAN_FP16);
	CONSTANT(CUDART_NEG_ZERO_FP16);
	CONSTANT(CUDART_ZERO_FP16);
	CONSTANT(CUDART_ONE_FP16);
#undef CONSTANT
}

__global__ void k_half_arithmetic(void)
{
	half h1, h2, h3;
	float f1;

	h1 = __float2half(3.14);
	h2 = __float2half(3.14);

	h3 = __hmul(h1, h2);
	f1 = __half2float(h3);

	printf("%f\n", f1);
}

int main(int argc, char *argv[])
{
	k_half_constants<<<1, 1>>>();
	k_half_arithmetic<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
