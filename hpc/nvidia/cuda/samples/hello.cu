#include <stdio.h>

#include <cuda_runtime.h>


__global__ void cuda_hello(void)
{
	printf("Hello World from GPU!\n");
}

int main(void)
{
	cuda_hello<<<1,1>>>();
	return 0;
}
