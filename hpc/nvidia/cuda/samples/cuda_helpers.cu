// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <stdio.h>
#include <string.h>
#if defined(HAVE_HCCL)
#include <hc_runtime.h>
#include "hpcc_helpers.h"
#include "cuda2hccl.h"
#else
#include <cuda_runtime.h>
#include "cuda_helpers.h"
#endif


void gpu_init(int dev_id)
{
	int deviceId;

	cudaSetDevice(dev_id);
	gpu_check_gpu_error("Failed to initialize device!");
	cudaDeviceSetLimit(cudaLimitPrintfFifoSize, 1048576);

	cudaGetDevice(&deviceId);
	if (deviceId != dev_id) {
		fprintf(stderr, "Set device failed.\n");
		exit(1);
	}
}

/*< check GPU errors >*/
void gpu_check_gpu_error(const char *msg)
{
	cudaError_t err = cudaGetLastError();
	if (cudaSuccess != err) {
		printf("Cuda error: %s: %s\n", msg, cudaGetErrorString(err));
		exit(1);
	}
}

const char *gpu_name(int dev_id, char *buf, int buf_len)
{
	cudaDeviceProp prop;
	cudaError_t err = cudaGetDeviceProperties(&prop, dev_id);
	if (err != cudaSuccess) {
		return NULL;
	}
	strncpy(buf, prop.name, buf_len);
	return buf;
}
