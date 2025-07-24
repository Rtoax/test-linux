/**
 * cuda-12.9 struct cudaDeviceProp: commit d072d32dcb00 ("cuda: cudaGetDeviceProperties.cu: display more")
 */
#include <stdio.h>
#if defined(HAVE_HCCL)
#include <hc_runtime.h>
#include "hpcc_helpers.h"
#else
#include <cuda_runtime.h>
#include "cuda_helpers.h"
#endif


int main(void)
{
	int i;
#ifdef HAVE_HCCL
	hcDeviceProp_t prop;
	hc_init(0);
	hcGetDeviceProperties(&prop, 0);
#else
	cudaDeviceProp prop;
	cuda_init(0);
	cudaGetDeviceProperties(&prop, 0);
#endif

	printf("name %s\n", prop.name);

	printf("totalGlobalMem %ld (%.0lf GiB)\n",
		prop.totalGlobalMem, prop.totalGlobalMem / 1e9);
	printf("totalConstMem %ld >= blockDim.x * blockDim.y * blockDim.z\n",
		prop.totalConstMem);

	printf("maxThreadsPerBlock %d\n", prop.maxThreadsPerBlock);

	for (i = 0; i < 3; i++)
		printf("maxThreadsDim[%d] = %-8d >= blockDim.%s\n", i,
			prop.maxThreadsDim[i], "x\0y\0z\0" + (2 * i));

	for (i = 0; i < 3; i++)
		printf("maxGridSize[%d] = %-16d >= gridDim.%s\n", i,
			prop.maxGridSize[i], "x\0y\0z\0" + (2 * i));

	return 0;
}
