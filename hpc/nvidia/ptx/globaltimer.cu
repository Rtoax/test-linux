// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2026 Rong Tao */
#include <stdio.h>
#include <cuda_runtime.h>

/**
 * Function to read the GPU nanosecond timer in a kernel
 * see cuda-samples/Samples/6_Performance/cudaGraphsPerfScaling
 */
__device__ __forceinline__ unsigned long long __globaltimer(void)
{
	unsigned long long globaltimer;
	asm volatile("mov.u64 %0, %globaltimer;" : "=l"(globaltimer));
	return globaltimer;
}

__global__ void foo(void)
{
	printf("Hello from GPU, globaltimer=%d\n", __globaltimer());
}

int main(void)
{
	foo<<<1, 1, 0>>>();

	cudaDeviceSynchronize();
	return 0;
}
