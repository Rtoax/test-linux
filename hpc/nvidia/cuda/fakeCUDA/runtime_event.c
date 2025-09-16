// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <cuda.h>
#include <cuda_runtime.h>
#include <driver_types.h>
#include <sys/types.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

#include "device.h"
#include "debug.h"
#include "types.h"


/**
 * typedef __attribute__((device_builtin)) struct CUevent_st *cudaEvent_t;
 */
struct CUevent_st {
	size_t ns;
};


static inline unsigned long nsecs(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return ts.tv_sec * 1000000000UL + ts.tv_nsec;
}

cudaError_t cudaEventCreate(cudaEvent_t *event)
{
	cudaEvent_t ev = malloc(sizeof(struct CUevent_st));
	memset(ev, 0, sizeof(struct CUevent_st));
	*event = ev;
	return cudaSuccess;
}

cudaError_t cudaEventCreateWithFlags(cudaEvent_t *event, unsigned int flags)
{
	return cudaSuccess;
}

cudaError_t cudaEventDestroy(cudaEvent_t event)
{
	free(event);
	return cudaSuccess;
}

cudaError_t cudaEventElapsedTime(float *ms, cudaEvent_t start, cudaEvent_t end)
{
	size_t elapse = end->ns - start->ns;
	*ms = elapse / 1000000UL;
	return cudaSuccess;
}

cudaError_t cudaEventQuery(cudaEvent_t event)
{
	return cudaSuccess;
}

cudaError_t cudaEventRecord(cudaEvent_t event, cudaStream_t stream)
{
	event->ns = nsecs();
	return cudaSuccess;
}

cudaError_t cudaEventRecordWithFlags(cudaEvent_t event, cudaStream_t stream,
				     unsigned int flags)
{
	return cudaSuccess;
}

cudaError_t cudaEventSynchronize(cudaEvent_t event)
{
	return cudaSuccess;
}
