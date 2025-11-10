// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#include <malloc.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"

struct dev_mem {
	int dev_id;
	float *dev_mem;
	float *host_mem;
};

#define SZ_MEM	(1024 * 1024 * 512)

void dev_mem_alloc(int dev_id, struct dev_mem *dev)
{
	dev->dev_id = dev_id;
	cudaSetDevice(dev_id);
	cudaMalloc(&dev->dev_mem, SZ_MEM * sizeof(float));

}

int main(void)
{
	int i, devNum;
	struct dev_mem *devs;

	devNum = gpu_num();
	devs = (struct dev_mem *)malloc(devNum * sizeof(struct dev_mem));

	for (i = 0; i < devNum; i++) {
		dev_mem_alloc(i, &devs[i]);
	}

	free(devs);
	return 0;
}
