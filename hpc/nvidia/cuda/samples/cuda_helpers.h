// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
#pragma once

#define CUDA_BUG_CALL(CALL, ERROR_DO)	{				\
	cudaError_t __err = CALL;					\
	if (__err != cudaSuccess) {					\
		fprintf(stderr, "ERROR: Call %s failed, %s\n",		\
			#CALL, cudaGetErrorString(__err));		\
		ERROR_DO;						\
	}								\
}
#define CUDA_BUG_CALL_EXIT(CALL) CUDA_BUG_CALL(CALL, exit(-1))

#define CUDA_BLAS_BUG_CALL(CALL, ERROR_DO)	{			\
	cublasStatus_t __status = CALL;					\
	if (__status != CUBLAS_STATUS_SUCCESS) {			\
		fprintf(stderr, "ERROR: Blas %s failed, %s\n",		\
			#CALL, cublasGetStatusString(__status));	\
		ERROR_DO;						\
	}								\
}
#define CUDA_BLAS_BUG_CALL_EXIT(CALL) CUDA_BLAS_BUG_CALL(CALL, exit(-1))

void gpu_init(int dev_id);
void gpu_check_gpu_error(const char *msg);

const char *gpu_name(int dev_id, char *buf, int buf_len);
int gpu_clock_rate(int dev_id);
