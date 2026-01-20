// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025-2026 Rong Tao */
/**
 * https://docs.nvidia.com/cuda/cuda-runtime-api/group__CUDART__PEER.html
 */
#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"

int nGPUs = 0;

void p2p_display_info(void)
{
	int i, j, value, srcDev, dstDev, can;

	srcDev = 0;
	dstDev = 1;

	nGPUs = gpu_num();

	printf("CanAccessPeer\n");
	printf("%-4s", "GPU");
	for (i = 0; i < nGPUs; i++)
		printf("%-4d", i);
	printf("\n");
	for (i = 0; i < nGPUs; i++) {
		printf("%-4d", i);
		for (j = 0; j < nGPUs; j++) {
			CUDA_RUNTIME_CHECK_EXIT(cudaDeviceCanAccessPeer(&can, i, j));
			printf("%-4d", can);
			if (can) {
				CUDA_RUNTIME_CHECK_EXIT(cudaSetDevice(i));
				CUDA_RUNTIME_CHECK(
					cudaDeviceEnablePeerAccess(j, 0), );
				CUDA_RUNTIME_CHECK(
					cudaDeviceDisablePeerAccess(j), );
			}
		}
		printf("\n");
	}

#define P2PAttr(attr) do {	\
		cudaDeviceGetP2PAttribute(&value, attr, srcDev, dstDev);	\
		printf("%s %d\n", #attr, value);	\
	} while (0)

	P2PAttr(cudaDevP2PAttrPerformanceRank);
	P2PAttr(cudaDevP2PAttrAccessSupported);
	P2PAttr(cudaDevP2PAttrNativeAtomicSupported);
	P2PAttr(cudaDevP2PAttrCudaArrayAccessSupported);
}

void p2p_memory_transfer(void)
{
	int i;
	float *s, *d;
	size_t size = 1024 * 1024; /* 1MB */
	cudaError_t err;

	printf("Memory copy\n");

	printf("%-4s", "GPU");
	for (i = 0; i < nGPUs; i++)
		printf("%-4d", i);
	printf("\n");
	for (int src = 0; src < nGPUs; src++) {
		printf("%-4d", src);
		for (int dst = 0; dst < nGPUs; dst++) {
			CUDA_RUNTIME_CHECK_EXIT(cudaSetDevice(src));
			CUDA_RUNTIME_CHECK_EXIT(cudaMalloc(&s, size));

			CUDA_RUNTIME_CHECK_EXIT(cudaSetDevice(dst));
			CUDA_RUNTIME_CHECK_EXIT(cudaMalloc(&d, size));

			err = cudaMemcpyPeer(d, dst, s, src, size);
			printf("%-4d", err == cudaSuccess ? 1 : 0);

			CUDA_RUNTIME_CHECK_EXIT(cudaFree(d));
			CUDA_RUNTIME_CHECK_EXIT(cudaFree(s));
		}
		printf("\n");
	}
}

int main(void)
{
	p2p_display_info();
	p2p_memory_transfer();

	return 0;
}
