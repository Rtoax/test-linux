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

#define SZ_MEM	(1024 * 1024 * 1024)

void dev_mem_alloc(int dev_id, struct device *dev)
{
	dev->dev_id = dev_id;
	cudaSetDevice(dev_id);
	cudaMalloc(&dev->dev_mem, SZ_MEM);
	cudaMemset(dev->dev_mem, 0, SZ_MEM);
	dev->host_mem = malloc(SZ_MEM);
}

void dev_mem_free(struct device *dev)
{
	cudaFree(dev->dev_mem);
	free(dev->host_mem);
}

void dev_mem_copy(struct device *from, struct device *to, cudaMemcpyKind kind,
		  float *elapse_ms)
{
	void *from_mem, *to_mem;
	cudaEvent_t start, end;

	switch (kind) {
	case cudaMemcpyDeviceToHost:
		from_mem = from->dev_mem;
		to_mem = to->host_mem;
		break;
	case cudaMemcpyHostToDevice:
		from_mem = from->host_mem;
		to_mem = to->dev_mem;
		break;
	case cudaMemcpyDeviceToDevice:
		from_mem = from->dev_mem;
		to_mem = to->dev_mem;
		break;
	case cudaMemcpyDefault:
	default:
		fprintf(stderr, "ERROR: unknown kind\n");
		return;
	}

	cudaEventCreate(&start);
	cudaEventCreate(&end);

	cudaEventRecord(start, NULL);

	CUDA_CHECK(cudaMemcpy(to_mem, from_mem, SZ_MEM, kind),);

	cudaEventRecord(end, NULL);
	cudaEventSynchronize(end);

	cudaEventElapsedTime(elapse_ms, start, end);
	cudaDeviceSynchronize();
}

void test_memcpy(struct device *devices, int devNum, cudaMemcpyKind kind)
{
	int i, j;

	printf("%-5s ", "\0");
	for (i = 0; i < devNum; i++) {
		printf("GPU%-5d", i);
	}
	printf("\n");
	for (i = 0; i < devNum; i++) {
		printf("GPU%-2d ", i);
		for (j = 0; j < devNum; j++) {
			float ms = 0;
			dev_mem_copy(&devices[i], &devices[j], kind, &ms);
			printf("%-7.2f ", ms);
		}
		printf("\n");
	}
}

int main(void)
{
	int i, devNum;
	struct device *devices;

	devNum = gpu_num();
	devices = (struct device *)malloc(devNum * sizeof(struct device));

	for (i = 0; i < devNum; i++) {
		dev_mem_alloc(i, &devices[i]);
	}

	printf("cudaMemcpyHostToDevice\n");
	test_memcpy(devices, devNum, cudaMemcpyHostToDevice);
	printf("cudaMemcpyDeviceToHost\n");
	test_memcpy(devices, devNum, cudaMemcpyDeviceToHost);
	printf("cudaMemcpyDeviceToDevice\n");
	test_memcpy(devices, devNum, cudaMemcpyDeviceToDevice);

	for (i = 0; i < devNum; i++) {
		dev_mem_free(&devices[i]);
	}

	free(devices);
	return 0;
}
