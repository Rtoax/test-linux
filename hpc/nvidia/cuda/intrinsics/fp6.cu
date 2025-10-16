// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * https://docs.nvidia.com/cuda/cuda-math-api/cuda_math_api/group__CUDA__MATH__INTRINSIC__FP6.html
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


__global__ void k_fp6_types(void)
{
#if !defined(__HPCC__) && !defined(__HIPCC__) && CUDA_VERSION >= 12000
	__nv_fp6_storage_t __unused fp6;
	__nv_fp6x2_storage_t __unused fp6x2;
	__nv_fp6x4_storage_t __unused fp6x4;
#else
# warning "Not support FP6"
#endif
}

int main(int argc, char *argv[])
{
	k_fp6_types<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
