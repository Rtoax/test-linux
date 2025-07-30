// SPDX-License-Identifier: GPL-3.0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#if defined(HAVE_HCCL)
# include <hc_runtime.h>
# include "hpcc_helpers.h"
# include "cuda2hccl.h"
#else
# include <cuda_runtime.h>
# include "cuda_helpers.h"
#endif

int main(int argc, char *argv[])
{
	float t_ms;
	cudaEvent_t ev_start, ev_stop;

	gpu_init(0);

	cudaEventCreate(&ev_start);
	cudaEventCreate(&ev_stop);

	cudaEventRecord(ev_start);

	/* some thing */
	sleep(1);

	cudaEventRecord(ev_stop);
	cudaEventSynchronize(ev_stop);

	cudaEventElapsedTime(&t_ms, ev_start, ev_stop);
	printf("GPU Elapsed %.6f ms\n", t_ms);

	cudaEventDestroy(ev_start);
	cudaEventDestroy(ev_stop);

	return 0;
}
