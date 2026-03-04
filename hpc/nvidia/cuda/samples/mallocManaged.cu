// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025-2026 Rong Tao */
/**
 * cudaMallocManaged:
 * When ease of programming is more important than extreme performance, or
 * when data access patterns alternate between CPU and GPU and are
 * unpredictable.
 *
 * see also cudaMallocHost()
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <cuda_runtime.h>
#include "cuda_helpers.h"


__managed__ __device__ int dev_managed_a = 0;
#ifdef ERROR
/* error: __managed__ variables cannot be marked __shared__ or __constant__ */
__managed__ __constant__ __device__ int dev_managed_const_a = 0;
#endif

__global__ void kernel_set1(int *mem, size_t nmemb)
{
	size_t i;
	for (i = 0; i < nmemb; i++)
		mem[i] = 1;
}

int main(void)
{
	int *ptr;
	int gpu_id = 0;
	size_t i, nmemb = 128;
	size_t size = nmemb * sizeof(*ptr);

	gpu_init(gpu_id);

	cudaMallocManaged(&ptr, size, cudaMemAttachGlobal);

#if defined(HAVE_HPCC) || defined(HAVE_HIP) || defined(HAVE_LUCA) || \
	defined(USE_CU_BRIDGE)
	cudaMemAdvise(ptr, size, cudaMemAdviseSetReadMostly, gpu_id);
#else
	cudaMemLocation location;
	location.id = gpu_id;
	location.type = cudaMemLocationTypeDevice;
	cudaMemAdvise(ptr, size, cudaMemAdviseSetReadMostly, location);
#endif

	memset(ptr, 0, size);

	kernel_set1<<<1, 1>>>(ptr, size);

#if !defined(ERROR)
	cudaDeviceSynchronize();
#endif

	for (i = 0; i < nmemb; i++)
		if (ptr[i] != 1)
			fprintf(stderr, "Bad ptr[%ld] = %d\n", i, ptr[i]);

	cudaFree(ptr);

	return 0;
}
