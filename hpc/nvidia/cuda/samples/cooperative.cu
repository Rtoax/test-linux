// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#if defined(HAVE_HCCL)
#include <hc_runtime.h>
#include <hpcc_cooperative_groups.h>
#include "hpcc_helpers.h"
#include "cuda2hccl.h"
#else
#include <cuda_runtime.h>
#include <cooperative_groups.h>
#include "cuda_helpers.h"
#endif

namespace cg = cooperative_groups;

__global__ void kernel(void)
{
	cg::thread_group g = cg::this_thread_block();

	int rank = g.thread_rank();
	int size = g.size();
	//bool valid = g.is_valid();
	bool valid = 0;

	extern __shared__ int temp[];

	/**
	 * If access temp[512 / sizeof(int)], metax trigger an error (memory
	 * access offset is negative, out of bounds), thus, metax page size is
	 * 512? error log see:
	 * - commit 1bf55db4e15b ("cuda: cooperative: use __shared__ and shareBytes")
	 */
	temp[rank] = rank;

	/**
	 * Some sync APIs
	 */
	__syncthreads();
	g.sync();
	cg::this_thread_block().sync();

	printf("rank %d, size %d, valid %d\n", rank, size, valid);

	/* FIXME: printf display wrong/zero %d, add printf could fix it. */
	#if defined(HAVE_HCCL)
	printf("");
	#endif
}

int main(void)
{
	int n, blksz, nblks, sharebytes;
	cudaStream_t stream;
	int *val;

	gpu_init(0);

	n = 4;
	blksz = 8;
	nblks = (n + blksz - 1) / blksz;
	sharebytes = blksz * sizeof(int);

	cudaMallocManaged(&val, n * sizeof(int));

	cudaStreamCreate(&stream);

	cudaLaunchCooperativeKernel((void *)kernel, nblks, blksz, NULL,
				    sharebytes, stream);

	cudaStreamSynchronize(stream);
	cudaStreamDestroy(stream);
	return 0;
}
