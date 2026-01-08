// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2026 Rong Tao */
#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"

__global__ void kernelHello(char *str)
{
	printf("Hello from GPU, %s.\n", str);
}

__global__ void squareArray(const float *input, float *output, int numElements)
{
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if (idx < numElements) {
		output[idx] = input[idx] * input[idx];
	}
}

/**
 * https://github.com/NVIDIA/cuda-samples.git
 * Samples/3_CUDA_Features/graphMemoryNodes/graphMemoryNodes.cu
 */
void graph_memory_square(int device)
{
	float *d_input, *d_square;
	float *input, *square;
	size_t numElements = 16;
	size_t bytes = numElements * sizeof(*input);
	cudaStream_t stream;
	cudaGraph_t graph;
	cudaGraphExec_t graphExec;
	cudaGraphNode_t allocNodeInput, allocNodeSquare;
	cudaGraphNode_t copyNodeInput, copyNodeSquare;
	cudaGraphNode_t squareKernelNode;
	cudaGraphNode_t freeNodeInput, freeNodeSquare;
	cudaMemAllocNodeParams allocParams;
	cudaKernelNodeParams kernelNodeParams = {0};

	input = (float *)malloc(bytes);
	square = (float *)malloc(bytes);

	for (size_t i = 0; i < numElements; i++)
		input[i] = 2.f;

	CUDA_RUNTIME_CHECK_EXIT(cudaGraphCreate(&graph, 0));

	memset(&allocParams, 0, sizeof(allocParams));
	allocParams.bytesize = bytes;
	allocParams.poolProps.allocType = cudaMemAllocationTypePinned;
	allocParams.poolProps.location.id = device;
	allocParams.poolProps.location.type = cudaMemLocationTypeDevice;

	CUDA_RUNTIME_CHECK_EXIT(cudaGraphAddMemAllocNode(
		&allocNodeInput, graph, NULL, 0, &allocParams));
	d_input = (float *)allocParams.dptr;

	/* allocNodeSquare should depend on allocNodeInput */
	CUDA_RUNTIME_CHECK_EXIT(cudaGraphAddMemAllocNode(
		&allocNodeSquare, graph, &allocNodeInput, 1, &allocParams));
	d_square = (float *)allocParams.dptr;

	CUDA_RUNTIME_CHECK_EXIT(cudaGraphAddMemcpyNode1D(
		&copyNodeInput, graph, &allocNodeSquare, 1, d_input, input,
		bytes, cudaMemcpyHostToDevice));

	void *squareKernelArgs[3] = { (void *)&d_input, (void *)&d_square,
				      (void *)&numElements };
	kernelNodeParams.gridDim = dim3(512, 1, 1);
	kernelNodeParams.blockDim = dim3(512, 1, 1);
	kernelNodeParams.sharedMemBytes = 0;
	kernelNodeParams.extra = NULL;
	kernelNodeParams.func = (void *)squareArray;
	kernelNodeParams.kernelParams = (void **)squareKernelArgs;

	CUDA_RUNTIME_CHECK_EXIT(cudaGraphAddKernelNode(&squareKernelNode, graph,
						       &copyNodeInput, 1,
						       &kernelNodeParams));

	CUDA_RUNTIME_CHECK_EXIT(cudaGraphAddMemcpyNode1D(
		&copyNodeSquare, graph, &squareKernelNode, 1, square, d_square,
		bytes, cudaMemcpyDeviceToHost));

	CUDA_RUNTIME_CHECK_EXIT(cudaGraphAddMemFreeNode(
		&freeNodeInput, graph, &squareKernelNode, 1, d_input));
	CUDA_RUNTIME_CHECK_EXIT(cudaGraphAddMemFreeNode(
		&freeNodeSquare, graph, &squareKernelNode, 1, d_square));

	CUDA_RUNTIME_CHECK_EXIT(
		cudaGraphInstantiate(&graphExec, graph, NULL, NULL, 0));
	CUDA_RUNTIME_CHECK_EXIT(cudaGraphDestroy(graph));

	CUDA_RUNTIME_CHECK_EXIT(
		cudaStreamCreateWithFlags(&stream, cudaStreamNonBlocking));
	CUDA_RUNTIME_CHECK_EXIT(cudaGraphLaunch(graphExec, stream));
	CUDA_RUNTIME_CHECK_EXIT(cudaStreamSynchronize(stream));
	CUDA_RUNTIME_CHECK_EXIT(cudaStreamDestroy(stream));
	CUDA_RUNTIME_CHECK_EXIT(cudaGraphExecDestroy(graphExec));

	for (size_t i = 0; i < numElements; i++)
		printf("input[%ld] ^ 2 = square[%ld] = %f ^ 2 = %f\n", i, i,
		       input[i], square[i]);
	free(input);
	free(square);
}

void graph_from_stream(void)
{
	char *dev_str;
	char host_str[128] = { "Rong Tao" };
	cudaStream_t stream;
	cudaGraph_t graph;
	cudaGraphExec_t graphExec;

	CUDA_RUNTIME_CHECK_EXIT(
		cudaStreamCreateWithFlags(&stream, cudaStreamNonBlocking));

	CUDA_RUNTIME_CHECK_EXIT(
		cudaStreamBeginCapture(stream, cudaStreamCaptureModeGlobal));

	CUDA_RUNTIME_CHECK_EXIT(
		cudaMallocAsync((void **)&dev_str, sizeof(host_str), stream));
	CUDA_RUNTIME_CHECK_EXIT(
		cudaMemcpyAsync(dev_str, host_str, sizeof(host_str),
				cudaMemcpyHostToDevice, stream));

	kernelHello<<<1, 1, 0, stream>>>(dev_str);

	CUDA_RUNTIME_CHECK_EXIT(cudaFreeAsync(dev_str, stream));

	CUDA_RUNTIME_CHECK_EXIT(cudaStreamEndCapture(stream, &graph));

	CUDA_RUNTIME_CHECK_EXIT(
		cudaGraphInstantiate(&graphExec, graph, NULL, NULL, 0));
	CUDA_RUNTIME_CHECK_EXIT(cudaGraphDestroy(graph));

	CUDA_RUNTIME_CHECK_EXIT(cudaGraphLaunch(graphExec, stream));

	CUDA_RUNTIME_CHECK_EXIT(cudaStreamSynchronize(stream));
	CUDA_RUNTIME_CHECK_EXIT(cudaStreamDestroy(stream));
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

	graph_memory_square(device);
	graph_from_stream();

	return 0;
}
