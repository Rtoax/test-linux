#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"


__global__ void kern_func(char *str)
{
	printf("Hello from GPU, %s.\n", str);
}

int main(void)
{
	char *dev_str;
	char host_str[128] = {"Rong Tao"};
	int prio = -1;
	cudaStream_t stream;

	gpu_init(0);

	cudaStreamCreate(&stream);

	cudaStreamGetPriority(stream, &prio);
	printf("Prio %d\n", prio);

	cudaMallocAsync((void **)&dev_str, sizeof(host_str), stream);
	cudaMemcpyAsync(dev_str, host_str, sizeof(host_str),
			cudaMemcpyHostToDevice, stream);

	kern_func<<<1, 1, 0, stream>>>(dev_str);

	cudaFreeAsync(dev_str, stream);

	cudaStreamSynchronize(stream);

#ifdef __LUCA__
	/* flush printf */
	cudaDeviceSynchronize();
#endif

	cudaStreamDestroy(stream);
	return 0;
}
