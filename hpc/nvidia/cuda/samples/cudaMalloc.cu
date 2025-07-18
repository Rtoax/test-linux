#include <stdio.h>
#include <cuda_runtime.h>

#include "cuda_helpers.h"


int main(void)
{
	int num= 1024;
	float *ptr;

	cudaSetDevice(0);
	cuda_check_gpu_error("Failed to initialize device!");

	cudaMalloc(&ptr, sizeof(*ptr) * num);
	cudaFree(ptr);

	return 0;
}
