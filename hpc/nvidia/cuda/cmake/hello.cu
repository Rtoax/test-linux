// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2024-2026 Rong Tao */
#include <stdio.h>
#include <cuda_runtime.h>

__global__ void kern_func(void)
{
	printf("Hello from GPU\n");
}

int main(void)
{
	kern_func<<<1, 1, 0>>>();
	cudaDeviceSynchronize();
	return 0;
}
