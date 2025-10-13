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

int main(int argc, char *argv[])
{
	assert(sizeof(__nv_bfloat16) == 2 && "bad size of half");

	k_bfloat16_constants<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
