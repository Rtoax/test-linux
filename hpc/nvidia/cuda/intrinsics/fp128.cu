// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * Note that FP128 CUDA Math functions are only available to device programs on
 * platforms where host compiler supports the basic quad precision datatype
 * __float128 or _Float128.
 *
 * https://docs.nvidia.com/cuda/cuda-math-api/cuda_math_api/group__CUDA__MATH__QUAD.html
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
#include "types.h"

#if !defined(__HPCC__) && !defined(__LUCA__)
# define SUPPORT_FP128
#endif

#if defined(SUPPORT__Float128)
# define fp128	_Float128
#elif defined(SUPPORT___float128)
# define fp128	__float128
#endif

__global__ void k_float128_types(void)
{
/**
 * error: "__float128" is a 128-bit floating-point, which is not supported in device code
 */
#if !defined(__NVCC__)
	fp128 f128 = 3.14;
#endif
}

int main(int argc, char *argv[])
{
	assert(sizeof(fp128) == 16 && "bad size of fp128");

	fp128 f128 = 3.14;

	k_float128_types<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
