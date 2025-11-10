// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include <stdio.h>
#include <malloc.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"

struct device {
	int dev_id;
	void *dev_mem;
	void *host_mem;
};

#define SZ_MEM	(1024 * 1024 * 512)

void dev_mem_alloc(int dev_id, struct device *dev)
{
	printf("Alloc memory for device %d\n", dev_id);
	dev->dev_id = dev_id;
	cudaSetDevice(dev_id);
	cudaMalloc(&dev->dev_mem, SZ_MEM);
	cudaMemset(dev->dev_mem, 0, SZ_MEM);
	dev->host_mem = malloc(SZ_MEM);
}

void dev_mem_free(struct device *dev)
{
	printf("Free memory of device %d\n", dev->dev_id);
	cudaFree(dev->dev_mem);
	free(dev->host_mem);
}

void dev_mem_copy(struct device *from, struct device *to, int flags)
{
}

int main(void)
{
	int i, j, devNum;
	struct device *devices;

	devNum = gpu_num();
	devices = (struct device *)malloc(devNum * sizeof(struct device));

	for (i = 0; i < devNum; i++) {
		dev_mem_alloc(i, &devices[i]);
	}

	for (i = 0; i < devNum; i++) {
		for (j = 0; j < devNum; j++) {
		}
	}

	for (i = 0; i < devNum; i++) {
		dev_mem_free(&devices[i]);
	}

	free(devices);
	return 0;
}
