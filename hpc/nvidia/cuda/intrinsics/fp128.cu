// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
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


__global__ void k_float128_types(void)
{
	//__float128 fp128 = make_float128(1.0);
}

int main(int argc, char *argv[])
{
	assert(sizeof(__float128) == 16 && "bad size of __float128");

	k_float128_types<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
