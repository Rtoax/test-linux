// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
#pragma once

#define CUDA_BUG_CALL(CALL, ERROR_DO)	{				\
	cudaError_t __err = CALL;					\
	if (__err != cudaSuccess) {					\
		fprintf(stderr, "ERROR: Call %s failed\n", #CALL);	\
		ERROR_DO;						\
	}								\
}

void gpu_init(int dev_id);
void gpu_check_gpu_error(const char *msg);
const char *gpu_name(int dev_id, char *buf, int buf_len);
