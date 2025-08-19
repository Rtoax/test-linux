#include <stdio.h>
#if defined(HAVE_HCCL)
#include <hccl.h>
#include <hc_runtime.h>
#include <hc_runtime_api.h>
#include "hpcc_helpers.h"
#include "cuda2hccl.h"
#else
#include <cuda.h>
#include <cuda_runtime.h>
#include "cuda_helpers.h"
#endif


int main(void)
{
	int value, dev_id;

	dev_id = 0;

	gpu_init(dev_id);

#define Attr(attr) do {	\
		cudaDeviceGetAttribute(&value, attr, dev_id);	\
		printf("%s %d\n", #attr, value);	\
	} while (0)

	Attr(cudaDevAttrMaxThreadsPerBlock);
	Attr(cudaDevAttrClockRate);
	Attr(cudaDevAttrMaxThreadsPerMultiProcessor);

	return 0;
}
