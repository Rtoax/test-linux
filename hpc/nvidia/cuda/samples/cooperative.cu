// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#if defined(HAVE_HCCL)
#include <hc_runtime.h>
#include <hpcc_cooperative_groups.h>
#include "hpcc_helpers.h"
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
	printf("");
}

int main(void)
{
	gpu_init(0);

	// TODO

	kernel<<<1, 2>>>();
	return 0;
}
