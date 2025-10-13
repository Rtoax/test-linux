#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"


int main(void)
{
	int value, dev_id;

	dev_id = 0;

	gpu_init(dev_id);

#define Attr(attr) do {	\
		cudaDeviceGetAttribute(&value, attr, dev_id);	\
		printf("%-64s %d\n", #attr, value);	\
	} while (0)

	Attr(cudaDevAttrEccEnabled);
	Attr(cudaDevAttrManagedMemory);
	Attr(cudaDevAttrL2CacheSize);
	Attr(cudaDevAttrClockRate);
	Attr(cudaDevAttrMaxThreadsPerBlock);
	Attr(cudaDevAttrMaxThreadsPerMultiProcessor);
#if !defined(__HIPCC__)
	Attr(cudaDevAttrHostNumaId);
#endif
	Attr(cudaDevAttrWarpSize);

	return 0;
}
