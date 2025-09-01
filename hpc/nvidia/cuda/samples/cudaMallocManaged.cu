// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#if defined(HAVE_HCCL)
#include <hc_runtime.h>
#include "hpcc_helpers.h"
#include "cuda2hccl.h"
#else
#include <cuda_runtime.h>
#include "cuda_helpers.h"
#endif


int main(void)
{
	int num= 1024;
	float *ptr;

	gpu_init(0);

	cudaMallocManaged(&ptr, sizeof(*ptr) * num);

	cudaFree(ptr);

	return 0;
}
