// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#if defined(HAVE_HPCC)
# include <hc_runtime.h>
# include "hpcc_helpers.h"
# include "cuda_adapter.h"
#elif defined(HAVE_HIP)
#include <hip/hip_runtime.h>
#include "cuda_helpers.h"
#include "cuda_adapter.h"
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

/**
 *                     sleep()     kernel     EvSync
 * Whole: |<-------->|<-------->|<-------->|<-------->|<-------->|
 */
int main(int argc, char *argv[])
{
	int dev_id;
	unsigned long start, elapse1, elapse2;
	float ev_ms1;
	cudaEvent_t ev_start, ev_stop;
	int clock_rate;

	dev_id = 0;

	gpu_init(dev_id);

	clock_rate = gpu_clock_rate(dev_id);

	cudaEventCreate(&ev_start);
	cudaEventCreate(&ev_stop);

	cudaEventRecord(ev_start, NULL);
	start = nsecs();

	/* do some thing */
	sleep(1);
	kernel<<<2, 2>>>(clock_rate * 1000);

	elapse1 = nsecs() - start;

	cudaEventRecord(ev_stop, NULL);
	cudaEventSynchronize(ev_stop);

	elapse2 = nsecs() - start;

	cudaEventElapsedTime(&ev_ms1, ev_start, ev_stop);

	printf("CUDA Elapsed %.6f ms\n", ev_ms1);
	printf("SYS Elapsed1 %ld ms\n", elapse1 / 1000000UL);
	printf("SYS Elapsed2 %ld ms\n", elapse2 / 1000000UL);

	cudaEventDestroy(ev_start);
	cudaEventDestroy(ev_stop);

	return 0;
}
