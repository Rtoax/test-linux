#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"


void display_info(void)
{
	int i, j, value, srcDev, dstDev, nGPUs, can;

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

int main(void)
{
	cudaDeviceDisablePeerAccess(0);
	display_info();

	return 0;
}
