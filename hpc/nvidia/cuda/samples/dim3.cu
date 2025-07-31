// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
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

__global__ void checkIndex(int it)
{
	int ix = threadIdx.x + blockDim.x * blockIdx.x;
	int iy = threadIdx.y + blockDim.y * blockIdx.y;
	int iz = threadIdx.z + blockDim.z * blockIdx.z;

	if (ix % it != 0 || iy % it != 0 || iz % it != 0)
		return;

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
}

int main(int argc, char *argv[])
{
	int i, bx, by, bz, gx, gy, gz, it;

	gpu_init(0);

	it = 1;
	bx = gx = 3;
	by = gy = 1;
	bz = gz = 1;

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
#undef arg_eq
	}

	fprintf(stderr, "Usage: %s [bx|by|bz|gx|gy|gz=<N>] [it=<INTERVAL>]\n", argv[0]);
	fprintf(stderr, "<<< grid(%d,%d,%d), block(%d,%d,%d) >>>\n",
		gx, gy, gz, bx, by, bz);

	dim3 block(bx, by, bz);
	dim3 grid(gx, gy, gz);

	checkIndex<<<grid, block>>>(it);

	/* flush printf */
	cudaDeviceSynchronize();

	return 0;
}
