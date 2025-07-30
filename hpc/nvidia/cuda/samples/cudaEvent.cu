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

static inline unsigned long nsecs(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec * 1000000000UL + ts.tv_nsec;
}

__device__ void busy_sleep(clock_t cycles)
{
	clock_t start = clock64();
	while (clock64() - start < cycles);
}

__global__ void kernel(clock_t cycles)
{
	busy_sleep(cycles);
}

int main(int argc, char *argv[])
{
	int dev_id;
	unsigned long start, end;
	float t_ms;
	cudaEvent_t ev_start, ev_stop;
	int clock_rate;

	dev_id = 0;

	gpu_init(dev_id);

	clock_rate = gpu_clock_rate(dev_id);

	cudaEventCreate(&ev_start);
	cudaEventCreate(&ev_stop);

	cudaEventRecord(ev_start);

	start = nsecs();

	/* some thing */
	sleep(1);
	kernel<<<2, 2>>>(clock_rate * 1000);

	end = nsecs();

	cudaEventRecord(ev_stop);
	cudaEventSynchronize(ev_stop);

	cudaEventElapsedTime(&t_ms, ev_start, ev_stop);

	printf("GPU Elapsed %.6f ms\n", t_ms);
	printf("Clock get time %ld ms\n", (end - start) / 1000000UL);

	cudaEventDestroy(ev_start);
	cudaEventDestroy(ev_stop);

	return 0;
}
