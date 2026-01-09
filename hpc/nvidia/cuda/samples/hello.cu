// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2024-2026 Rong Tao */
/**
 * elf sections of metax: commit 047883bd3538 ("metax: hello.hpcc: ELF section info")
 * elf sections of cuda:  commit bd1c08a6a95f ("cuda: hello.c: see elf sections")
 * elf dump PTX and SASS: commit 306555e1b4e6 ("nvidia: PTX and SASS")
 */
#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"


__device__ int dev_a = 0;
__constant__ __device__ int dev_const_a = 0;

/* call by kernel/device, run by device */
__device__ void dev_foo(void)
{
	printf("Hello from GPU foo, laneid=%d.\n", __lane_id());
}

/* call by host, run by device */
__global__ void kern_func(void)
{
#ifdef __HPCC_ARCH__
	/* Device code */
#else
	/* Host code */
#endif
	printf("Hello from GPU.\n");
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

#ifdef __LUCA__
	/* flush printf */
	cudaDeviceSynchronize();
#endif
	return 0;
}
