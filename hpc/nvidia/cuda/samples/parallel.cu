// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"


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

/**
 * CUDA: cuobjdump -sass fatbin0.elf
 * HIP: llvm-objdump -d fatbin0.elf
 *
 * - commit bf095f941a58 ("hpc: isa/elf compare: hip, cuda, hpcc")
 */
__global__ void kernel_bar(int count)
{
}

/**
 * CUDA: cuobjdump -sass fatbin0.elf
 * HIP: llvm-objdump -d fatbin0.elf
 *
 * - commit bf095f941a58 ("hpc: isa/elf compare: hip, cuda, hpcc")
 */
__global__ void kernel_bar1(int count)
{
	__syncthreads();
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
