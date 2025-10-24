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
			cudaDeviceCanAccessPeer(&can, i, j);
			printf("%-4d", can);
			if (can) {
				cudaSetDevice(i);
				CUDA_CHECK(cudaDeviceEnablePeerAccess(j, 0),);
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
#if defined(HAVE_HPCC)
	P2PAttr(hcDevP2PAttrHcArrayAccessSupported);
#endif
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
			cudaSetDevice(src);
			cudaMalloc(&s, size);

			cudaSetDevice(dst);
			cudaMalloc(&d, size);

			err = cudaMemcpyPeer(d, dst, s, src, size);
			printf("%-4d", err == cudaSuccess ? 1 : 0);

			cudaFree(d);
			cudaFree(s);
		}
		printf("\n");
	}
}

int main(void)
{
	cudaDeviceDisablePeerAccess(0);
	p2p_display_info();
	p2p_memory_transfer();

	return 0;
}
