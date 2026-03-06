// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2026 Rong Tao */
#include <assert.h>
#include <stdio.h>
#include <cuda_runtime.h>

extern "C" __global__ void assert_kernel(void)
{
	assert(1 > 2);
}

int main(void)
{
	assert_kernel<<<1, 1, 0>>>();
	/* flush printf */
	cudaDeviceSynchronize();
	return 0;
}
