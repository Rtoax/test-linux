#include "cuda_compat.h"
#include "cuda_helpers.h"

__global__ void kernel_1(void)
{
	printf("kernel\n");
}

int main(void)
{
	kernel_1<<<1, 1>>>();
	cudaDeviceSynchronize();
	return 0;
}
