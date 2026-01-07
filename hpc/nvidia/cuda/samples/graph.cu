// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2026 Rong Tao */
#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"


/**
 * https://github.com/NVIDIA/cuda-samples.git
 * Samples/3_CUDA_Features/graphMemoryNodes/graphMemoryNodes.cu
 */
void graph_memory(int device)
{
	float *d_input, *d_square;
	cudaGraph_t graph;
	cudaGraphNode_t allocNodeInput, allocNodeSquare;
	cudaGraphNode_t copyNodeInput, copyNodeSquare;
	cudaGraphExec_t exec;
	cudaMemAllocNodeParams allocParams;
	cudaKernelNodeParams kernelNodeParams = {0};

	allocParams.bytesize = 1024;
	allocParams.poolProps.allocType = cudaMemAllocationTypePinned;
	allocParams.poolProps.location.id = device;
	allocParams.poolProps.location.type = cudaMemLocationTypeDevice;

	kernelNodeParams.gridDim = dim3(512, 1, 1);
	kernelNodeParams.blockDim = dim3(512, 1, 1);
	kernelNodeParams.sharedMemBytes = 0;
	kernelNodeParams.extra = NULL;

	cudaGraphCreate(&graph, 0);
	cudaGraphAddMemAllocNode(&allocNodeInput, graph, NULL, 0, &allocParams);
	d_input = (float *)allocParams.dptr;

	cudaGraphAddMemAllocNode(&allocNodeSquare, graph, &allocNodeInput, 1, &allocParams);
	d_square = (float *)allocParams.dptr;

	//cudaGraphAddMemcpyNode1D(&copyNodeInput, graph, &allocNodeSquare);

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

	graph_memory(device);

	return 0;
}
