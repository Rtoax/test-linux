// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#if defined(HAVE_HPCC)
#include <hc_runtime.h>
#include "cuda_adapter.h"
#elif defined(HAVE_HIP)
#include <hip/hip_runtime.h>
#include "cuda_adapter.h"
#else
#include <cuda_runtime.h>
#endif
#include "cuda_helpers.h"


int main(void)
{
	int num= 1024;
	float *ptr;

	gpu_init(0);

	cudaMalloc(&ptr, sizeof(*ptr) * num);
	cudaMemset(ptr, 0, sizeof(*ptr) * num);
	cudaFree(ptr);

	return 0;
}
