// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2026 Rong Tao */
/**
 * cudaError_t cudaMemPoolCreate(cudaMemPool_t *memPool, const struct cudaMemPoolProps *poolProps);
 * cudaError_t cudaMemPoolDestroy(cudaMemPool_t memPool);
 */
#include <argp.h>
#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"

int main(int argc, char *argv[])
{
	cudaMemPool_t pool;
	cudaMemPoolProps props = {};

	props.allocType = cudaMemAllocationTypePinned;
	props.location.id = 0; /* device id */
	props.location.type = cudaMemLocationTypeDevice;

	cudaMemPoolCreate(&pool, &props);

	cudaMemPoolDestroy(pool);
	return 0;
}
