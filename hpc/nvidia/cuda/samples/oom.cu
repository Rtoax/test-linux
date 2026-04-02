// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2026 Rong Tao */
#include <stdio.h>
#include <cuda_runtime.h>
#include "cuda_helpers.h"

#define KiB 1024
#define MiB (KiB * 1024)
#define GiB (MiB * 1024)

__global__ void kern_pagefault(void *mem, size_t sz)
{
	for (size_t i = 0; i < sz; i += 4096)
		*(char *)((char *)mem + i) = i % 26 + 'a';
}

int main(void)
{
	void *mem;
	size_t total = 0;

	for (;;) {
		size_t blksz = MiB;
		CUDA_RUNTIME_CHECK(cudaMalloc(&mem, blksz), break);
		kern_pagefault<<<1, 1, 0>>>(mem, blksz);
		total += blksz;
		printf("Alloc %ld B, %ld MiB, %ld GiB\n", total, total / MiB,
		       total / GiB);
	}

	/* flush printf */
	cudaDeviceSynchronize();
	return 0;
}
