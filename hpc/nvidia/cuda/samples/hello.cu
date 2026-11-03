// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2024-2026 Rong Tao. All rights reserved. */
/**
 * elf sections of metax: commit 047883bd3538 ("metax: hello.hpcc: ELF section info")
 * elf sections of cuda:  commit bd1c08a6a95f ("cuda: hello.c: see elf sections")
 * elf dump PTX and SASS: commit 306555e1b4e6 ("nvidia: PTX and SASS")
 */
#include <stdio.h>
#include <cuda_runtime.h>
#include "cuda_helpers.h"
#include "cuda_kernel_misc.h"

#define CALL_KERNEL(func, ...) func<<<1, 1, 0>>>(__VA_ARGS__)

__device__ int dev_a = 0;
__constant__ __device__ int dev_const_a = 0;
char *g_p = NULL;

/* call by kernel/device, run by device */
__device__ void dev_foo(const char *name)
{
	/* warpSize is a constant in kernel */
	printf("Hello from GPU %s, laneid=%d, warpSize = %d.\n", name,
	       __laneid(), warpSize);
}

/* call by host, run by device */
__global__ void kern_func(void *p)
{
	dev_foo("func");
	printf("%s: p = %p\n", __func__, p);

	__syncthreads();
}

__global__ void kern_func1(int a1)
{
	dev_foo("func1");

	__syncthreads();
}

/* call,run by host */
__host__ void host_func(void)
{
}

int main(void)
{
	gpu_init(0);

	cudaMalloc(&g_p, 64);

	printf("g_p = %p\n", g_p);

	CALL_KERNEL(kern_func, g_p);
	CALL_KERNEL(kern_func1, 1);
	host_func();

	cudaFree(g_p);

	/* flush printf */
	cudaDeviceSynchronize();
	return 0;
}
