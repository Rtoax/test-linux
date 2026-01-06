// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2026 Rong Tao */
#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"


/**
 * https://github.com/NVIDIA/cuda-samples.git
 * Samples/3_CUDA_Features/graphMemoryNodes/graphMemoryNodes.cu
 */
void graph_memory(void)
{
	cudaGraph_t graph;
	cudaGraphNode_t node;
	cudaGraphExec_t exec;

	cudaGraphCreate(&graph, 0);

	//cudaGraphAddMemcpyNode1D();

	cudaGraphDestroy(graph);
}

int main(void)
{
	int device = 0;
	int driverVersion = 0;
	int deviceSupportsMemoryPools = 0;

	cudaDriverGetVersion(&driverVersion);
	printf("Driver version is: %d.%d\n", driverVersion / 1000, (driverVersion % 100) / 10);

#ifdef __NVCC__
	if (driverVersion < 11040) {
		printf("Waiving execution as driver does not support Graph Memory Nodes\n");
		exit(1);
	}
#endif

	cudaDeviceGetAttribute(&deviceSupportsMemoryPools, cudaDevAttrMemoryPoolsSupported, device);
	if (!deviceSupportsMemoryPools) {
		printf("Waiving execution as device does not support Memory Pools\n");
		exit(1);
	}

	return 0;
}
