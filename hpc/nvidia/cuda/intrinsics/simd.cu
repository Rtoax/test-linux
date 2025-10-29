// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * https://docs.nvidia.com/cuda/cuda-math-api/cuda_math_api/group__CUDA__MATH__INTRINSIC__SIMD.html
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


__global__ void k_simd_types(void)
{
	short2 s;
	s.x = 1;
	s.y = 2;
	PSHORT2(s);
}

__global__ void k_simd_abs2(void)
{
	/* -123 and 456 */
	unsigned int input = (0xFF85u << 16) | 0x01C8u;
	unsigned int result = __vabs2(input);

	short2 input_short2 = *reinterpret_cast<short2 *>(&input);
	short2 result_short2 = *reinterpret_cast<short2 *>(&result);

	PSHORT2(input_short2);
	PSHORT2(result_short2);
}

int main(int argc, char *argv[])
{
	k_simd_types<<<1, 1>>>();
	k_simd_abs2<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
