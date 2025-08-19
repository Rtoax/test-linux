// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#if defined(HAVE_HCCL)
#include <hc_runtime.h>
#include "hpcc_helpers.h"
#include "cuda2hccl.h"
#else
#include <cuda_runtime.h>
#include "cuda_helpers.h"
#endif


__global__ void foo(int count)
{
	int id = threadIdx.x + blockDim.x * blockIdx.x;
	if (id >= count)
		return;
	/* do something */
}

int main(void)
{
	int count = 10000;

	gpu_init(0);

	foo<<<(count + 511) / 512, 512>>>(count);
	return 0;
}
