#include <stdio.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"


int main(void)
{
	int dev_id, count;

	/**
	 * TODO: how to choice default device
	 */
	cudaGetDevice(&dev_id);
	cudaGetDeviceCount(&count);
	printf("dev %d, count %d\n", dev_id, count);

	cudaSetDevice(1);
	cudaGetDevice(&dev_id);
	printf("dev %d\n", dev_id);

	return 0;
}
