// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025-2026 Rong Tao */
/**
 * https://docs.nvidia.com/cupti/api/group__CUPTI__ACTIVITY__API.html
 */
#include <stdio.h>
#include <cupti.h>
#include <cuda_runtime.h>
#include "cuda_helpers.h"

__device__ void foo(void)
{
	printf("foo\n");
}

__global__ void kernel_1(void)
{
	foo();
	printf("kernel\n");
}

static void BufferRequested(uint8_t **buffer, size_t *size, size_t *maxNumRecords)
{
	*size = 8 * 1024 * 1024; /* 8MB buffer */
	*maxNumRecords = 0;
	*buffer = (uint8_t*)malloc(*size);
}

static void BufferCompleted(CUcontext ctx, uint32_t streamId, uint8_t *buffer,
			    size_t size, size_t validSize)
{
	CUpti_Activity *record = NULL;

	if (validSize > 0) {
		/**
		 * Parse CUPTI activity records here, print kernel name and
		 * duration
		 */
		while (cuptiActivityGetNextRecord(buffer, validSize, &record) == CUPTI_SUCCESS) {
			if (record->kind == CUPTI_ACTIVITY_KIND_CONCURRENT_KERNEL) {
#ifdef __LUCA__
				CUpti_ActivityKernel8 *kernel = (CUpti_ActivityKernel8 *)record;
#else
				CUpti_ActivityKernel10 *kernel = (CUpti_ActivityKernel10 *)record;
#endif
				printf("kernel name = %s\n", kernel->name);
				printf("kernel duration (ns) = %llu\n",
					(unsigned long long)(kernel->end - kernel->start));
			}
		}
	}
	free(buffer);
}

int main(void)
{
	CUPTI_CHECK_EXIT(cuptiActivityRegisterCallbacks(BufferRequested, BufferCompleted));
	CUPTI_CHECK_EXIT(cuptiActivityEnable(CUPTI_ACTIVITY_KIND_CONCURRENT_KERNEL));

	kernel_1<<<1, 1>>>();

	cudaDeviceSynchronize();

	CUPTI_CHECK_EXIT(cuptiActivityFlushAll(1));
	CUPTI_CHECK_EXIT(cuptiActivityDisable(CUPTI_ACTIVITY_KIND_CONCURRENT_KERNEL));
	return 0;
}
