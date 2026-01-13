// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2025-2026 Rong Tao */
/**
 * See also https://github.com/NVIDIA/cuda-samples.git
 * cuda-samples/Samples/1_Utilities/bandwidthTest/bandwidthTest.cu
 *
 * Memory copy tests:
 * - commit b4a41493a8a1 ("memory.cu: Memcpy: LingSpeed X710-M OAM 10GB")
 */
#include <argp.h>
#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include "cuda_compat.h"
#include "cuda_helpers.h"

#define KiB	1024
#define MiB	(KiB * 1024)
#define GiB	(MiB * 1024)

#define MEMCOPY_ITERATIONS	100
#define DEFAULT_SIZE	(32 * MiB)

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
	.size = DEFAULT_SIZE,
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
	CUDA_RUNTIME_CHECK_EXIT(cudaSetDevice(dev_id));
	CUDA_RUNTIME_CHECK_EXIT(cudaMalloc(&dev->dev_mem, env.size));
	CUDA_RUNTIME_CHECK_EXIT(cudaMemset(dev->dev_mem, 0, env.size));
	dev->host_mem = malloc(env.size);
}

void dev_mem_free(struct device *dev)
{
	if (env.verbose)
		printf("Free memory of device %d\n", dev->dev_id);
	CUDA_RUNTIME_CHECK_EXIT(cudaFree(dev->dev_mem));
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

	CUDA_RUNTIME_CHECK_EXIT(cudaEventCreate(&start));
	CUDA_RUNTIME_CHECK_EXIT(cudaEventCreate(&end));

	CUDA_RUNTIME_CHECK_EXIT(cudaEventRecord(start, NULL));

	for (unsigned int i = 0; i < MEMCOPY_ITERATIONS; i++) {
		CUDA_RUNTIME_CHECK(cudaMemcpy(to_mem, from_mem, env.size, kind),
				   assert(0 && "Memcpy"));
	}

	CUDA_RUNTIME_CHECK_EXIT(cudaEventRecord(end, NULL));
	CUDA_RUNTIME_CHECK_EXIT(cudaEventSynchronize(end));

	CUDA_RUNTIME_CHECK_EXIT(cudaEventElapsedTime(elapse_ms, start, end));

	CUDA_RUNTIME_CHECK_EXIT(cudaEventDestroy(start));
	CUDA_RUNTIME_CHECK_EXIT(cudaEventDestroy(end));
}

void test_memcpy(struct device *devices, int devNum, cudaMemcpyKind kind)
{
	int i, j;

	printf("%-5s ", "GB/s");
	for (i = 0; i < devNum; i++) {
		printf("GPU%-3d ", i);
	}
	printf("\n");
	for (i = 0; i < devNum; i++) {
		printf("GPU%-2d ", i);
		for (j = 0; j < devNum; j++) {
			if (i == j) {
				printf("%-7s", "-");
				continue;
			}
			float ms = 0;
			dev_mem_copy(&devices[i], &devices[j], kind, &ms);
			double time_s = ms / 1e3;
			double bandwidthGBs = .0f;
			bandwidthGBs = (2.f * env.size * (float)MEMCOPY_ITERATIONS) / GiB;
			bandwidthGBs /= time_s;
			printf("%-7.2lf", bandwidthGBs);
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
