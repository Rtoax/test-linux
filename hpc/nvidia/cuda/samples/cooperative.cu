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
	printf("rank %llu\n", g.thread_rank());

	/* FIXME: printf display wrong/zero %d, add printf could fix it. */
	#if defined(HAVE_HCCL)
	printf("");
	#endif
}

int main(void)
{
	cudaStream_t stream;

	gpu_init(0);

	cudaStreamCreate(&stream);

	cudaLaunchCooperativeKernel(kernel, 3, 2, NULL, 0, stream);
	//kernel<<<1, 2>>>();

	cudaStreamSynchronize(stream);
	cudaStreamDestroy(stream);
	return 0;
}
