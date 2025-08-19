#include <stdio.h>
#if defined(HAVE_HCCL)
#include <hc_runtime.h>
#include "hpcc_helpers.h"
#include "cuda2hccl.h"
#else
#include <cuda_runtime.h>
#include "cuda_helpers.h"
#endif


int main(void)
{
	int value, srcDev, dstDev, can;

	srcDev = 0;
	dstDev = 1;

	cudaDeviceCanAccessPeer(&can, srcDev, dstDev);
	printf("%d -> %d %s\n", srcDev, dstDev, can ? "can" : "can't");

#define P2PAttr(attr) do {	\
		cudaDeviceGetP2PAttribute(&value, attr, srcDev, dstDev);	\
		printf("%s %d\n", #attr, value);	\
	} while (0)

	P2PAttr(cudaDevP2PAttrPerformanceRank);
	P2PAttr(cudaDevP2PAttrAccessSupported);
	P2PAttr(cudaDevP2PAttrNativeAtomicSupported);
#if defined(HAVE_HCCL)
	P2PAttr(hcDevP2PAttrHcArrayAccessSupported);
#endif

	return 0;
}
