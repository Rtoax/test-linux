/**
 * - NVIDIA H800 device properties
 *   commit 3e9b58b99824 ("cudaGetDeviceProperties: blockDim,gridDim")
 *   commit f803951f1f66 ("hpc: get more device prop of Nvidia H800 and MetaX Mars 03")
 * - MetaX Mars 03 device properties
 *   commit 4117d2538707 ("metax: Display Mars 03 DeviceProperties")
 *   commit f803951f1f66 ("hpc: get more device prop of Nvidia H800 and MetaX Mars 03")
 * - cuda-12.9 struct cudaDeviceProp
 *   commit d072d32dcb00 ("cuda: cudaGetDeviceProperties.cu: display more")
 */
#include <stdio.h>
#if defined(HAVE_HCCL)
#include <hc_runtime.h>
#include "hpcc_helpers.h"
#include "cuda2hccl.h"
#else
#include <cuda_runtime.h>
#include "cuda_helpers.h"
#endif


int main(void)
{
	int i;
#ifdef HAVE_HCCL
	hcDeviceProp_t prop;
#else
	cudaDeviceProp prop;
#endif

	gpu_init(0);

	cudaGetDeviceProperties(&prop, 0);

	printf("name %s\n", prop.name);

	printf("totalGlobalMem %ld (%.0lf GiB)\n",
		prop.totalGlobalMem, prop.totalGlobalMem / 1e9);
	printf("totalConstMem %ld\n", prop.totalConstMem);
	printf("multiProcessorCount %d\n", prop.multiProcessorCount);
	printf("maxThreadsPerMultiProcessor %d\n", prop.maxThreadsPerMultiProcessor);
	printf("Theoretical number of concurrent hardware threads: %d\n",
		prop.multiProcessorCount * prop.maxThreadsPerMultiProcessor);

	printf("maxThreadsPerBlock %d >= blockDim.x * blockDim.y * blockDim.z\n",
		prop.maxThreadsPerBlock);

	for (i = 0; i < 3; i++)
		printf("maxThreadsDim[%d] = %-8d >= blockDim.%s\n", i,
			prop.maxThreadsDim[i], "x\0y\0z\0" + (2 * i));

	for (i = 0; i < 3; i++)
		printf("maxGridSize[%d] = %-16d >= gridDim.%s\n", i,
			prop.maxGridSize[i], "x\0y\0z\0" + (2 * i));

	printf("major %d, minor %d\n", prop.major, prop.minor);

	return 0;
}
