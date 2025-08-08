// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
#pragma once

#define CUDA_CHECK(CALL, ERROR_DO)	{				\
	cudaError_t __err = CALL;					\
	if (__err != cudaSuccess) {					\
		fprintf(stderr, "ERROR: Call %s failed, %s\n",		\
			#CALL, cudaGetErrorString(__err));		\
		ERROR_DO;						\
	}								\
}
#define CUDA_CHECK_EXIT(CALL) CUDA_CHECK(CALL, exit(-1))

#define CUBLAS_CHECK(CALL, ERROR_DO)	{				\
	cublasStatus_t __status = CALL;					\
	if (__status != CUBLAS_STATUS_SUCCESS) {			\
		fprintf(stderr, "ERROR: Blas %s failed, %s\n",		\
			#CALL, cublasGetStatusString(__status));	\
		ERROR_DO;						\
	}								\
}
#define CUBLAS_CHECK_EXIT(CALL) CUBLAS_CHECK(CALL, exit(-1))

#define CURAND_CHECK(CALL, ERROR_DO)	{				\
	curandStatus_t __status = CALL;					\
	if (__status != CURAND_STATUS_SUCCESS) {			\
		fprintf(stderr, "ERROR: Rand %s failed, %d\n",		\
			#CALL, __status);				\
		ERROR_DO;						\
	}								\
}

void gpu_init(int dev_id);
void gpu_check_gpu_error(const char *msg);

const char *gpu_name(int dev_id, char *buf, int buf_len);
int gpu_clock_rate(int dev_id);
int gpu_max_threads_per_block(int dev_id);
