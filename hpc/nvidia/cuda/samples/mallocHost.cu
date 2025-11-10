// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#include "cuda_compat.h"
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

	CUDA_CHECK(cudaMallocHost(&ptr, sizeof(*ptr) * num, 0), exit(1));
	CUDA_CHECK(cudaMemset(ptr, 0, sizeof(*ptr) * num), exit(1));

	hexdump(ptr, sizeof(*ptr) * num);

	kernel_write_mem<<<1, 1>>>(ptr, sizeof(*ptr) * num);

	hexdump(ptr, sizeof(*ptr) * num);

	CUDA_CHECK(cudaFreeHost(ptr), exit(1));

	/* flush printf */
	cudaDeviceSynchronize();
	return 0;
}
