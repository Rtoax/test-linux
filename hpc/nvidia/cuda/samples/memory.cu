// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025 Rong Tao */
/**
 * Memory copy tests:
 * - commit b4a41493a8a1 ("memory.cu: Memcpy: LingSpeed X710-M OAM 10GB")
 */
#include <argp.h>
#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"

struct device {
	int dev_id;
	void *dev_mem;
	void *host_mem;
};

struct {
	bool verbose;
	unsigned long size;
} env = {
	.verbose = false,
	.size = 1024 * 1024 * 512,
};

const char *version = "v0.0.1";

const char argp_prog_doc[] =
	"USAGE: [-v]\n"
	"\n";

static const struct argp_option opts[] = {
	{ "size", 'S', "SIZE", 0, "Memory size" },
	{ "verbose", 'v', NULL, 1, "Display detail" },
	{ "version", 'V', NULL, 1, "Display version" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'S':
		env.size = strtoul(arg, NULL, 10);
		break;
	case 'v':
		env.verbose = true;
		break;
	case 'V':
		printf("%s\n", version);
		exit(EXIT_SUCCESS);
		break;
	case ARGP_KEY_ARG:
		break;
	case ARGP_KEY_END:
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static const struct argp argp = {
	.options = opts,
	.parser = parse_arg,
	.doc = argp_prog_doc,
};

void dev_mem_alloc(int dev_id, struct device *dev)
{
	if (env.verbose)
		printf("Alloc memory for device %d\n", dev_id);
	dev->dev_id = dev_id;
	cudaSetDevice(dev_id);
	cudaMalloc(&dev->dev_mem, env.size);
	cudaMemset(dev->dev_mem, 0, env.size);
	dev->host_mem = malloc(env.size);
}

void dev_mem_free(struct device *dev)
{
	if (env.verbose)
		printf("Free memory of device %d\n", dev->dev_id);
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
	case cudaMemcpyHostToHost:
		from_mem = from->host_mem;
		to_mem = to->host_mem;
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

	CUDA_CHECK(cudaMemcpy(to_mem, from_mem, env.size, kind),);

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

int main(int argc, char *argv[])
{
	int i, err, devNum;
	struct device *devices;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	gpu_init(0);

	devNum = gpu_num();
	devices = (struct device *)malloc(devNum * sizeof(struct device));

	if (env.verbose) {
		printf("Total %d GPUs\n", devNum);
		printf("Memory size %ld\n", env.size);
	}

	for (i = 0; i < devNum; i++) {
		dev_mem_alloc(i, &devices[i]);
	}

	printf("cudaMemcpyHostToHost\n");
	test_memcpy(devices, devNum, cudaMemcpyHostToHost);
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
