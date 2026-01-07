// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2026 Rong Tao */
#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"


__global__ void kern_func(char *str)
{
	printf("Hello from GPU, %s.\n", str);
}

int main(void)
{
	char *dev_str;
	char host_str[128] = {"Rong Tao"};
	int prio = -1;
	cudaStream_t stream;

	gpu_init(0);

#ifdef CREATE_GRAPH_FROM_STREAM
	cudaGraph_t graph;
#endif

	/**
	 * cudaStreamCreate(&stream);
	 * cudaStreamCreateWithFlags(&stream, cudaStreamDefault=0);
	 */
	cudaStreamCreateWithFlags(&stream, cudaStreamNonBlocking);

	cudaStreamGetPriority(stream, &prio);
	printf("Prio %d\n", prio);

#ifdef CREATE_GRAPH_FROM_STREAM
	cudaStreamBeginCapture(stream, cudaStreamCaptureModeGlobal);
#endif

	cudaMallocAsync((void **)&dev_str, sizeof(host_str), stream);
	cudaMemcpyAsync(dev_str, host_str, sizeof(host_str),
			cudaMemcpyHostToDevice, stream);

	kern_func<<<1, 1, 0, stream>>>(dev_str);

	cudaFreeAsync(dev_str, stream);

#ifdef CREATE_GRAPH_FROM_STREAM
	cudaStreamEndCapture(stream, &graph);
#endif

	cudaStreamSynchronize(stream);

#ifdef __LUCA__
	/* flush printf */
	cudaDeviceSynchronize();
#endif

	cudaStreamDestroy(stream);
	return 0;
}
