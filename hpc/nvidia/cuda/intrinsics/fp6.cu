// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025-2026 Rong Tao */
/**
 * https://docs.nvidia.com/cuda/cuda-math-api/cuda_math_api/group__CUDA__MATH__INTRINSIC__FP6.html
 */
#if !defined(__HPCC__) && !defined(__LUCA__) && !defined(__HIPCC__) && CUDA_VERSION > 12040
# define __have_fp6
#else
# warning "Not support FP6"
#endif

#include <stdio.h>
#include <cuda_runtime.h>
#if defined(__have_fp6)
#include <cuda_fp6.h>
#endif
#include "compiler.h"
#include "print.h"
#include "types.h"


__global__ void k_fp6_types(void)
{
#if defined(__have_fp6)
	__nv_fp6_storage_t __unused fp6;
	__nv_fp6x2_storage_t __unused fp6x2;
	__nv_fp6x4_storage_t __unused fp6x4;
#endif
}

int main(int argc, char *argv[])
{
	k_fp6_types<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
