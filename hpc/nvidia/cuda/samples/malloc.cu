// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025-2026 Rong Tao */
#include <stdio.h>
#include <string.h>
#include <cuda_runtime.h>
#include "cuda_helpers.h"

int main(void)
{
	int num = 1024;
	float *ptr, *host_ptr;
	size_t size;

	gpu_init(0);

	size = sizeof(*ptr) * num;

	host_ptr = (float *)malloc(size);
	memset(host_ptr, 0, size);

	cudaMalloc(&ptr, size);
	cudaMemset(ptr, 0, size);

	cudaMemcpy(ptr, host_ptr, size, cudaMemcpyHostToDevice);
	cudaMemcpy(ptr, ptr, size, cudaMemcpyDeviceToDevice);
	cudaMemcpy(host_ptr, ptr, size, cudaMemcpyDeviceToHost);
	cudaMemcpy(host_ptr, host_ptr, size, cudaMemcpyHostToHost);

	cudaFree(ptr);
	free(host_ptr);

	return 0;
}
