#include <stdio.h>
#if defined(HAVE_HPCC)
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

int main(void)
{
	int count;
	cudaGetDeviceCount(&count);
	printf("count %d\n", count);
	return 0;
}
