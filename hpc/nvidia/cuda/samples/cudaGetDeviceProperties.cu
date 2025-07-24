/**
 * cuda-12.9 struct cudaDeviceProp: commit d072d32dcb00 ("cuda: cudaGetDeviceProperties.cu: display more")
 */
#include <stdio.h>
#include <cuda_runtime.h>
#include "cuda_helpers.h"


int main(void)
{
	int i;
	cudaDeviceProp prop;

	cuda_init(0);

	cudaGetDeviceProperties(&prop, 0);

	printf("name %s\n", prop.name);
	printf("totalGlobalMem %ld (%.0lf GiB)\n",
		prop.totalGlobalMem, prop.totalGlobalMem / 1e9);
	printf("totalConstMem %ld\n", prop.totalConstMem);
	printf("maxThreadsPerBlock %d\n", prop.maxThreadsPerBlock);
	for (i = 0; i < 3; i++)
		printf("maxThreadsDim[%d] = %d\n", i, prop.maxThreadsDim[i]);
	for (i = 0; i < 3; i++)
		printf("maxGridSize[%d] = %d\n", i, prop.maxGridSize[i]);

	return 0;
}
