/**
 * elf sections of metax: commit 047883bd3538 ("metax: hello.hpcc: ELF section info")
 * elf sections of cuda:  commit bd1c08a6a95f ("cuda: hello.c: see elf sections")
 * elf dump PTX and SASS: commit 306555e1b4e6 ("nvidia: PTX and SASS")
 */
#include <stdio.h>
#if defined(HAVE_HCCL)
#include <hc_runtime.h>
#include "hpcc_helpers.h"
#include "cuda_adapter.h"
#elif defined(HAVE_HIP)
#include <hip/hip_runtime.h>
#include "cuda_helpers.h"
#include "cuda_adapter.h"
#else
/**
 * Actually, nvcc will add -include cuda_runtime.h during compile, thus, we
 * don't need this include line
 */
#include <cuda_runtime.h>
#include "cuda_helpers.h"
#endif

__device__ int dev_a = 0;
__constant__ __device__ int dev_const_a = 0;

/* call by kernel/device, run by device */
__device__ void dev_foo(void)
{
	printf("Hello from GPU foo.\n");
}

/* call by host, run by device */
__global__ void kern_func(void)
{
#ifdef __HPCC_ARCH__
	/* Device code */
#else
	/* Host code */
#endif
	printf("Hello from GPU.\n");
	dev_foo();

	__syncthreads();
}

/* call,run by host */
__host__ void host_func(void)
{
}

int main(void)
{
	cudaStream_t stream;

	gpu_init(0);

	cudaStreamCreate(&stream);

	kern_func<<<1, 1, 0, stream>>>();
	host_func();

	cudaStreamSynchronize(stream);

	/* flush printf */
	cudaDeviceSynchronize();

	cudaStreamDestroy(stream);
	return 0;
}
