// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * grid, block, warps(wavefronts or waves), thread
 */
#include <stdio.h>
#include <string.h>
#if defined(HAVE_HCCL)
#include <hc_runtime.h>
#include "hpcc_helpers.h"
#include "cuda2hccl.h"
#else
#include <cuda_runtime.h>
#include "cuda_helpers.h"
#endif

__global__ void checkInfo(void)
{
	/**
	 * Threads are batched in groups that we’ll call Wavefronts or
	 * waves (or warps in Nvidia lingo), see
	 * https://flashypixels.wordpress.com/2018/11/10/intro-to-gpu-scalarization-part-1/
	 */
	printf("warpSize %d\n", warpSize);
#if !defined(__CUDACC__)
	printf("waveSize %d\n", waveSize);
#else
	printf("waveSize not support on CUDA.\n");
#endif
}

__global__ void checkIndex(int it)
{
	int ix = threadIdx.x + blockDim.x * blockIdx.x;
	int iy = threadIdx.y + blockDim.y * blockIdx.y;
	int iz = threadIdx.z + blockDim.z * blockIdx.z;

	if (ix % it != 0 || iy % it != 0 || iz % it != 0)
		return;

	__syncthreads();

	printf("threadIdx(%d,%d,%d), blockIdx(%d,%d,%d), blockDim(%d,%d,%d), gridDim(%d,%d,%d) (%d,%d,%d)\n",
		threadIdx.x, threadIdx.y, threadIdx.z,
		blockDim.x, blockDim.y, blockDim.z,
		blockIdx.x, blockIdx.y, blockIdx.z,
		gridDim.x, gridDim.y, gridDim.z,
		ix, iy, iz);
/**
 * FIXME: MetaX htcc have wrong threadIdx.x, add printf could fix it.
 */
#if defined(HAVE_HCCL)
	printf("");
#endif

	__syncthreads();

	if (ix == 0 && iy == 0 && iz == 0)
		printf("------ done ------\n");
}

int main(int argc, char *argv[])
{
	int i, it, bx, by, bz, gx, gy, gz, dim;

	gpu_init(0);

	it = 1;
	dim = 2;
	bx = gx = 2;
	by = gy = 2;
	bz = gz = 2;

	for (i = 1; i < argc; i++) {
#define arg_eq(v) if (!strncmp(#v"=", argv[i], strlen(#v) + 1)) \
			v = atoi(argv[i] + strlen(#v) + 1);
		arg_eq(bx);
		arg_eq(by);
		arg_eq(bz);
		arg_eq(gx);
		arg_eq(gy);
		arg_eq(gz);
		arg_eq(it);
		arg_eq(dim);
#undef arg_eq
	}

	dim3 block1(bx);
	dim3 grid1(gx);
	dim3 block2(bx, by);
	dim3 grid2(gx, gy);
	dim3 block3(bx, by, bz);
	dim3 grid3(gx, gy, gz);

	dim3 grid;
	dim3 block;

	fprintf(stderr, "Usage: %s [bx|by|bz|gx|gy|gz=<N>] [it=<INTERVAL>] [dim=<1|2|3>]\n", argv[0]);

	switch (dim) {
	case 3:
		grid = grid3;
		block = block3;
		break;
	case 2:
		grid = grid2;
		block = block2;
		break;
	case 1:
		grid = grid1;
		block = block1;
		break;
	default:
		fprintf(stderr, "ERROR: Not support dim=%d\n", dim);
		exit(EXIT_FAILURE);
	}

	fprintf(stderr, "<<< grid(%d,%d,%d), block(%d,%d,%d) >>>\n",
		grid.x, grid.y, grid.z, block.x, block.y, block.z);

	checkInfo<<<1, 1>>>();
	checkIndex<<<grid, block>>>(it);

	/* flush printf */
	cudaDeviceSynchronize();

	return 0;
}
