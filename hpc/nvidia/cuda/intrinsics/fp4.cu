// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2026 Rong Tao */
#include <cuda.h>
#if !defined(__HPCC__) && !defined(__LUCA__) && !defined(__HIPCC__) && \
	CUDA_VERSION > 12040
# define __have_fp4
#else
# warning "Not support FP4"
#endif
#include <assert.h>
#include <stdio.h>
#include <cuda_runtime.h>
#if defined(__have_fp4)
#include <cuda_fp4.h>
#endif
#include "compiler.h"
#include "print.h"
#include "types.h"

__global__ void k_fp4_types(void)
{
#if defined(__have_fp4)
	__nv_fp4_storage_t __unused fp4;
	__nv_fp4x2_storage_t __unused fp4x2;
	__nv_fp4x4_storage_t __unused fp4x4;
#endif
}

int main(int argc, char *argv[])
{
#if defined(__have_fp4)
	assert(sizeof(__nv_fp4_storage_t) == 1 &&
	       "bad size of __nv_fp4_storage_t");
	assert(sizeof(__nv_fp4x2_storage_t) == 1 &&
	       "bad size of __nv_fp4x2_storage_t");
	assert(sizeof(__nv_fp4x4_storage_t) == 2 &&
	       "bad size of __nv_fp4x4_storage_t");
#endif

	k_fp4_types<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
