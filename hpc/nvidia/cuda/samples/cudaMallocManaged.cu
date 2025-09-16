// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#if defined(HAVE_HCCL)
#include <hc_runtime.h>
#include "hpcc_helpers.h"
#include "cuda_adapter.h"
#else
#include <cuda_runtime.h>
#include "cuda_helpers.h"
#endif

__managed__ __device__ int dev_managed_a = 0;

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

	cudaMallocManaged(&ptr, size);

#if defined(HAVE_HCCL)
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
