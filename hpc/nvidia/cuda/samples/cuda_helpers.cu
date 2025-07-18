#include <stdio.h>
#include <cuda_runtime.h>


/*< check GPU errors >*/
void cuda_check_gpu_error(const char *msg)
{
	cudaError_t err = cudaGetLastError();
	if (cudaSuccess != err) {
		printf("Cuda error: %s: %s\n", msg, cudaGetErrorString(err));
		exit(0);
	}
}
