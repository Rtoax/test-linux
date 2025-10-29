// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * https://docs.nvidia.com/cuda/cuda-math-api/cuda_math_api/group__CUDA__MATH__INT.html
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


__global__ void k_integer_types(void)
{
}

int main(int argc, char *argv[])
{
	assert(sizeof(int) == 4 && "bad size of int");

	k_integer_types<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
