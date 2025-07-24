#include <stdio.h>
#include <cuda_runtime.h>
#include "cuda_helpers.h"


int main(void)
{
	cudaDeviceProp prop;

	cuda_init(0);

	cudaGetDeviceProperties(&prop, 0);

	printf("maxThreadsPerBlock %d\n", prop.maxThreadsPerBlock);

	return 0;
}
