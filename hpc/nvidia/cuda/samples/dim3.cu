#include <stdio.h>
#if defined(HAVE_HCCL)
#include <hc_runtime.h>
#include "hpcc_helpers.h"
#include "cuda2hccl.h"
#else
#include <cuda_runtime.h>
#include "cuda_helpers.h"
#endif

__global__ void checkIndex(void)
{
	printf("threadIdx(%d,%d,%d), blockIdx(%d,%d,%d), blockDim(%d,%d,%d), gridDim(%d,%d,%d)\n",
		threadIdx.x, threadIdx.y, threadIdx.z,
		blockDim.x, blockDim.y, blockDim.z,
		blockIdx.x, blockIdx.y, blockIdx.z,
		gridDim.x, gridDim.y, gridDim.z);
}

int main(void)
{
	int n = 6;
	dim3 block(3);
	dim3 grid((n + block.x - 1) / block.x);

	gpu_init(0);

	checkIndex<<<grid, block>>>();

	/* flush printf */
	cudaDeviceSynchronize();

	return 0;
}
