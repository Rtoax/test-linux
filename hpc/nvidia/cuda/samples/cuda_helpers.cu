#include <stdio.h>
#include <cuda_runtime.h>
#include "cuda_helpers.h"


void cuda_init(int dev_id)
{
	cudaSetDevice(0);
	cuda_check_gpu_error("Failed to initialize device!");
}

/*< check GPU errors >*/
void cuda_check_gpu_error(const char *msg)
{
	cudaError_t err = cudaGetLastError();
	if (cudaSuccess != err) {
		printf("Cuda error: %s: %s\n", msg, cudaGetErrorString(err));
		exit(0);
	}
}
