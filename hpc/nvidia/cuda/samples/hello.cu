/**
 * elf sections of cuda: commit bd1c08a6a95f ("cuda: hello.c: see elf sections")
 */

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
