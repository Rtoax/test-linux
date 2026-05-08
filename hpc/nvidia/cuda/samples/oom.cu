// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2026 Rong Tao */
#include <argp.h>
#include <stdio.h>
#include <cuda_runtime.h>
#include "cuda_helpers.h"

#define KiB 1024
#define MiB (KiB * 1024)
#define GiB (MiB * 1024)

const char argp_prog_doc[] = "USAGE: cuda oom [-v]\n\n";

static const struct argp_option opts[] = {
	{ "nopf", 'n', NULL, 1, "Disable page fault" },
	{ "managed", 'm', NULL, 1,
	  "Use cudaMallocManaged() instead of cudaMalloc()" },
	{},
};

struct {
	/**
	 * Actually, if not page-fault, the GPU Memory Usage still rise up, see
	 * nvidia-smi.
	 */
	bool nopagefault;
	bool managed;
} env = {
	.nopagefault = false,
	.managed = false,
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'n':
		env.nopagefault = true;
		break;
	case 'm':
		env.managed = true;
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
#if __cplusplus > 202002L
	.options = opts,
	.parser = parse_arg,
	.doc = argp_prog_doc,
#else
	opts,
	parse_arg,
	argp_prog_doc,
#endif
};

__global__ void kern_pagefault(void *mem, size_t sz)
{
	/**
	 * TODO: could use cuMemGetAllocationGranularity() get pagesize of HBM.
	 */
	for (size_t i = 0; i < sz; i += 4096)
		*(char *)((char *)mem + i) = i % 26 + 'a';
}

int main(int argc, char *argv[])
{
	int err;
	void *mem;
	size_t total = 0;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	for (;;) {
		size_t blksz = MiB;
		if (env.managed) {
			CUDA_RUNTIME_CHECK(
				cudaMallocManaged(&mem, blksz,
						  cudaMemAttachGlobal),
				break);
		} else {
			CUDA_RUNTIME_CHECK(cudaMalloc(&mem, blksz), break);
		}
		if (!env.nopagefault) {
			kern_pagefault<<<1, 1, 0>>>(mem, blksz);
		}
		total += blksz;
		printf("Alloc %ld B, %ld MiB, %ld GiB\n", total, total / MiB,
		       total / GiB);
	}

	/* flush printf */
	cudaDeviceSynchronize();
	return 0;
}
