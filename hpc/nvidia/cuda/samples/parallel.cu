#include <stdio.h>
#include <cuda_runtime.h>
#include "cuda_helpers.h"


__global__ void foo(int count)
{
	int id = threadIdx.x + blockDim.x * blockIdx.x;
	if (id >= count)
		return;
	/* do something */
}

int main(void)
{
	int count = 10000;

	gpu_init(0);

	foo<<<(count + 511) / 512, 512>>>(count);
	return 0;
}
