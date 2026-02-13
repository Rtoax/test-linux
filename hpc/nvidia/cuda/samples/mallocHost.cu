// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025-2026 Rong Tao */
/**
 * cudaMallocHost():
 * When you need to perform frequent data transfers, where data transfer
 * performance is critical, and you can manage explicit data transfers.
 *
 * see also cudaMallocManaged().
 */
#include <stdio.h>
#include <cuda_runtime.h>
#include "cuda_helpers.h"
#include "memshow.c"

__global__ void kernel_write_mem(void *mem, size_t sz)
{
	char *str = (char *)mem;
	for (size_t i = 0; i < sz; i++) {
		str[i]  = 'a';
	}
}

int main(void)
{
	int num = 10;
	float *ptr;

	gpu_init(0);

#ifdef __HIPCC__
	CUDA_RUNTIME_CHECK(hipMallocHost((void **)&ptr, sizeof(*ptr) * num),
			   exit(1));
#else
	CUDA_RUNTIME_CHECK(cudaMallocHost(&ptr, sizeof(*ptr) * num, 0),
			   exit(1));
#endif
	CUDA_RUNTIME_CHECK(cudaMemset(ptr, 0, sizeof(*ptr) * num), exit(1));

	hexdump(ptr, sizeof(*ptr) * num);

	kernel_write_mem<<<1, 1>>>(ptr, sizeof(*ptr) * num);

	cudaDeviceSynchronize();

	hexdump(ptr, sizeof(*ptr) * num);

	CUDA_RUNTIME_CHECK(cudaFreeHost(ptr), exit(1));

	/* flush printf */
	cudaDeviceSynchronize();
	return 0;
}
