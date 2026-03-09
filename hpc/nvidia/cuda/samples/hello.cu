// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2024-2026 Rong Tao */
/**
 * elf sections of metax: commit 047883bd3538 ("metax: hello.hpcc: ELF section info")
 * elf sections of cuda:  commit bd1c08a6a95f ("cuda: hello.c: see elf sections")
 * elf dump PTX and SASS: commit 306555e1b4e6 ("nvidia: PTX and SASS")
 */
#include <stdio.h>
#include <cuda_runtime.h>
#include "cuda_helpers.h"
#include "cuda_kernel_misc.h"

__device__ int dev_a = 0;
__constant__ __device__ int dev_const_a = 0;

/* call by kernel/device, run by device */
__device__ void dev_foo(void)
{
	/* warpSize is a constant in kernel */
	printf("Hello from GPU, laneid=%d, warpSize = %d.\n", __laneid(),
	       warpSize);
}

/* call by host, run by device */
__global__ void kern_func(void)
{
	dev_foo();

	__syncthreads();
}

/* call,run by host */
__host__ void host_func(void)
{
}

int main(void)
{
	gpu_init(0);

	kern_func<<<1, 1, 0>>>();
	host_func();

	/* flush printf */
	cudaDeviceSynchronize();
	return 0;
}
