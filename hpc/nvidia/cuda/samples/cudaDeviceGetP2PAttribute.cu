#include <stdio.h>
#if defined(HAVE_HPCC)
#include <hc_runtime.h>
#include "cuda_adapter.h"
#elif defined(HAVE_HIP)
#include <hip/hip_runtime.h>
#include "cuda_adapter.h"
#else
#include <cuda_runtime.h>
#endif
#include "cuda_helpers.h"


int main(void)
{
	int i, j, value, srcDev, dstDev, nGPUs, can;

	srcDev = 0;
	dstDev = 1;

	nGPUs = gpu_num();

	cudaDeviceDisablePeerAccess(0);

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

	return 0;
}
