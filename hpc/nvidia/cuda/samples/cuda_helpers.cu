// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <stdio.h>
#include <cuda_runtime.h>
#include "cuda_helpers.h"


void cuda_init(int dev_id)
{
	int deviceId;

	cudaSetDevice(dev_id);
	cuda_check_gpu_error("Failed to initialize device!");
	cudaDeviceSetLimit(cudaLimitPrintfFifoSize, 1048576);

	cudaGetDevice(&deviceId);
	if (deviceId != dev_id) {
		fprintf(stderr, "Set device failed.\n");
		exit(1);
	}
}

/*< check GPU errors >*/
void cuda_check_gpu_error(const char *msg)
{
	cudaError_t err = cudaGetLastError();
	if (cudaSuccess != err) {
		printf("Cuda error: %s: %s\n", msg, cudaGetErrorString(err));
		exit(1);
	}
}
