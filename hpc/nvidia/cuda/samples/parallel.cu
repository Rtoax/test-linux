// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#if defined(HAVE_HCCL)
#include <hc_runtime.h>
#include "hpcc_helpers.h"
#include "cuda_adapter.h"
#elif defined(HAVE_HIP)
#include <hip/hip_runtime.h>
#include "cuda_helpers.h"
#include "cuda_adapter.h"
#else
#include <cuda_runtime.h>
#include "cuda_helpers.h"
#endif

__device__ void kernel_device1(int id)
{
	printf("1 %d\n", id);
}

__device__ void kernel_device2(int id)
{
	printf("2 %d\n", id);
}

__device__ void kernel_device3(int id)
{
	printf("2 %d\n", id);
}

__global__ void kernel_foo(int count)
{
	int id = threadIdx.x + blockDim.x * blockIdx.x;
	if (id >= count)
		return;

	kernel_device1(id);

#ifdef __HPCC__
	cudaDeviceSynchronize();
#endif

	kernel_device2(id);
	kernel_device3(id);

	__syncthreads();
}

__global__ void kernel_bar(int count)
{
	int a = 3;
}

int main(void)
{
	int count = 10;

	printf("Startup...\n");

	gpu_init(0);

	kernel_foo<<<(count + 511) / 512, 512>>>(count);
	kernel_bar<<<(count + 511) / 512, 512>>>(count);

	/* flush printf */
	(void)cudaDeviceSynchronize();

	printf("Bye...\n");
	return 0;
}
