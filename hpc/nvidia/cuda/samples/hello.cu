/**
 * elf sections of cuda: commit bd1c08a6a95f ("cuda: hello.c: see elf sections")
 */

#include <stdio.h>
/**
 * Actually, nvcc will add -include cuda_runtime.h during compile, thus, we
 * don't need this include line
 */
#include <cuda_runtime.h>

#include "cuda_helpers.h"


__global__ void cuda_hello(void)
{
	printf("Hello World from GPU!\n");
}

int main(void)
{
	cudaSetDevice(0);
	cuda_check_gpu_error("Failed to initialize device!");

	cuda_hello<<<1,1>>>();
	return 0;
}
