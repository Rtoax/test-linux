#include <stdio.h>
#include <cuda_runtime.h>

#include "cuda_helpers.h"


int main(void)
{
	int num= 1024;
	float *ptr;

	cuda_init(0);

	cudaMalloc(&ptr, sizeof(*ptr) * num);
	cudaFree(ptr);

	return 0;
}
