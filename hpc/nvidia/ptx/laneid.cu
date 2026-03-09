// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2026 Rong Tao */
#include <stdio.h>
#include <cuda_runtime.h>

__device__ __forceinline__ unsigned int __laneid(void)
{
	unsigned int laneid;
	asm("mov.u32 %0, %%laneid;" : "=r"(laneid));
	return laneid;
}

__global__ void foo(void)
{
	printf("Hello from GPU, laneid=%d\n", __laneid());
}

int main(void)
{
	foo<<<1, 1, 0>>>();

	cudaDeviceSynchronize();
	return 0;
}
