// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * https://docs.nvidia.com/cuda/cublas/
 */
#include <math.h>
#include <string.h>
#include "blas.hpp"
#include "debug.h"
#include "types.h"


#ifdef HAVE_HPCC
#define cublasGetVersion_v2	hcblasGetVersion
#define cublasCreate_v2	hcblasCreate
#define cublasDestroy_v2	hcblasDestroy
#define cublasIsamax_v2	hcblasIsamax
#define cublasIdamax_v2	hcblasIdamax
#define cublasIsamin_v2	hcblasIsamin
#define cublasIdamin_v2	hcblasIdamin
#define cublasSasum_v2	hcblasSasum
#define cublasDasum_v2	hcblasDasum
#define cublasSscal_v2	hcblasSscal
#define cublasDscal_v2	hcblasDscal
#define cublasSaxpy_v2	hcblasSaxpy
#define cublasDaxpy_v2	hcblasDaxpy
#define cublasScopy_v2	hcblasScopy
#define cublasDcopy_v2	hcblasDcopy
#define cublasSdot_v2	hcblasSdot
#define cublasDdot_v2	hcblasDdot
#define cublasSnrm2_v2	hcblasSnrm2
#define cublasDnrm2_v2	hcblasDnrm2
#define cublasSgemm_v2	hcblasSgemm
#define cublasDgemm_v2	hcblasDgemm
#endif


cublasStatus_t cublasGetVersion_v2(cublasHandle_t handle, int *version)
{
	*version = 1300;
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasCreate_v2(cublasHandle_t *handle)
{
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasDestroy_v2(cublasHandle_t handle)
{
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasGetProperty(libraryPropertyType type, int *value)
{
	DEBUG_DBG("type %d\n", type);

	switch (type) {
	case MAJOR_VERSION:
		*value = 13;
		break;
	case MINOR_VERSION:
		*value = 0;
		break;
	case PATCH_LEVEL:
		*value = 0;
		break;
	default:
		return CUBLAS_STATUS_INVALID_VALUE;
	}
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasSetMatrix(int rows, int cols, int elemSize,
			       const void *A, int lda, void *B, int ldb)
{
	const char *src = (const char *)A;
	char *dst = (char*)B;

	for (int j = 0; j < cols; ++j) {
		memcpy(dst + j * ldb * elemSize,
			src + j * lda * elemSize,
			rows * elemSize);
	}
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasGetMatrix(int rows, int cols, int elemSize,
			       const void *A, int lda, void *B, int ldb)
{
	const char *src = (const char*)A;
	char *dst = (char*)B;
	for (int j = 0; j < cols; ++j) {
		memcpy(dst + j * ldb * elemSize,
			src + j * lda * elemSize,
			rows * elemSize);
	}
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasIsamax_v2(cublasHandle_t handle, int n,
			       const float *x, int incx, int *result)
{
	if (n <= 0)
		return CUBLAS_STATUS_INVALID_VALUE;

	int idx_max = 0;
	float max_val = fabsf(x[0]);
	for (int i = 1; i < n; ++i) {
		float val = fabsf(x[i * incx]);
		if (val > max_val) {
			max_val = val;
			idx_max = i;
		}
	}
	*result = idx_max;
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasIdamax_v2(cublasHandle_t handle, int n,
			       const double *x, int incx, int *result)
{
	if (n <= 0)
		return CUBLAS_STATUS_INVALID_VALUE;

	int idx_max = 0;
	double max_val = fabsf(x[0]);
	for (int i = 1; i < n; ++i) {
		double val = fabsf(x[i * incx]);
		if (val > max_val) {
			max_val = val;
			idx_max = i;
		}
	}
	*result = idx_max;
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasIsamin_v2(cublasHandle_t handle, int n,
			       const float *x, int incx, int *result)
{
	if (n <= 0)
		return CUBLAS_STATUS_INVALID_VALUE;

	int idx_min = 0;
	float min_val = fabsf(x[0]);
	for (int i = 1; i < n; ++i) {
		float val = fabsf(x[i * incx]);
		if (val < min_val) {
			min_val = val;
			idx_min = i;
		}
	}
	*result = idx_min;
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasIdamin_v2(cublasHandle_t handle, int n,
			       const double *x, int incx, int *result)
{
	if (n <= 0)
		return CUBLAS_STATUS_INVALID_VALUE;

	int idx_min = 0;
	double min_val = fabsf(x[0]);
	for (int i = 1; i < n; ++i) {
		double val = fabsf(x[i * incx]);
		if (val < min_val) {
			min_val = val;
			idx_min = i;
		}
	}
	*result = idx_min;
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasSasum_v2(cublasHandle_t handle, int n,
			      const float *x, int incx, float *result)
{
	float sum = 0.0f;
	for (int i = 0; i < n; ++i) {
		sum += fabsf(x[i * incx]);
	}
	*result = sum;

	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasDasum_v2(cublasHandle_t handle, int n,
			      const double *x, int incx, double *result)
{
	double sum = 0.0f;
	for (int i = 0; i < n; ++i) {
		sum += fabsf(x[i * incx]);
	}
	*result = sum;

	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasSscal_v2(cublasHandle_t handle, int n, const float *alpha,
			   float *x, int incx)
{
	for (int i = 0; i < n; ++i) {
		x[i * incx] = (*alpha) * x[i * incx];
	}
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasDscal_v2(cublasHandle_t handle, int n, const double *alpha,
			      double *x, int incx)
{
	for (int i = 0; i < n; ++i) {
		x[i * incx] = (*alpha) * x[i * incx];
	}
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasSaxpy_v2(cublasHandle_t handle, int n, const float *alpha,
			      const float *x, int incx,
			      float *y, int incy)
{
	for (int i = 0; i < n; ++i) {
		y[i * incy] += (*alpha) * x[i * incx];
	}
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasDaxpy_v2(cublasHandle_t handle, int n, const double *alpha,
			      const double *x, int incx,
			      double *y, int incy)
{
	for (int i = 0; i < n; ++i) {
		y[i * incy] += (*alpha) * x[i * incx];
	}
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasScopy_v2(cublasHandle_t handle, int n,
			      const float *x, int incx,
			      float *y, int incy)
{
	for (int i = 0; i < n; ++i) {
		y[i * incy] = x[i * incx];
	}
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasDcopy_v2(cublasHandle_t handle, int n,
			      const double *x, int incx,
			      double *y, int incy)
{
	for (int i = 0; i < n; ++i) {
		y[i * incy] = x[i * incx];
	}
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasSdot_v2(cublasHandle_t handle, int n,
			     const float *x, int incx,
			     const float *y, int incy,
			     float *result)
{
	float _result = 0.0f;
	for (int i = 0; i < n; ++i) {
		_result += x[i * incx] * y[i * incy];
	}
	*result = _result;

	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasDdot_v2(cublasHandle_t handle, int n,
			     const double *x, int incx,
			     const double *y, int incy,
			     double *result)
{
	double _result = 0.0f;
	for (int i = 0; i < n; ++i) {
		_result += x[i * incx] * y[i * incy];
	}
	*result = _result;

	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasSnrm2_v2(cublasHandle_t handle, int n,
			      const float *x, int incx, float *result)
{
	float sum = 0.0f;
	for (int i = 0; i < n; ++i) {
		float val = x[i * incx];
		sum += val * val;
	}
	*result = sqrtf(sum);

	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasDnrm2_v2(cublasHandle_t handle, int n,
			      const double *x, int incx, double *result)
{
	double sum = 0.0f;
	for (int i = 0; i < n; ++i) {
		double val = x[i * incx];
		sum += val * val;
	}
	*result = sqrtf(sum);

	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasSgemm_v2(cublasHandle_t handle,
			      cublasOperation_t transa, cublasOperation_t transb,
			      int m, int n, int k,
			      const float *alpha,
			      const float *A, int lda,
			      const float *B, int ldb,
			      const float *beta,
			      float *C, int ldc)
{
	for (int row = 0; row < m; ++row) {
		for (int col = 0; col < n; ++col) {
			float sum = 0.0f;
			for (int i = 0; i < k; ++i) {
				sum += A[row + i * lda] * B[i + col * ldb];
			}
			C[row + col * ldc] = (*alpha) * sum + (*beta) * C[row + col * ldc];
		}
	}
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasDgemm_v2(cublasHandle_t handle,
			      cublasOperation_t transa, cublasOperation_t transb,
			      int m, int n, int k,
			      const double *alpha,
			      const double *A, int lda,
			      const double *B, int ldb,
			      const double *beta,
			      double *C, int ldc)
{
	for (int row = 0; row < m; ++row) {
		for (int col = 0; col < n; ++col) {
			double sum = 0.0f;
			for (int i = 0; i < k; ++i) {
				sum += A[row + i * lda] * B[i + col * ldb];
			}
			C[row + col * ldc] = (*alpha) * sum + (*beta) * C[row + col * ldc];
		}
	}
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasHgemm(cublasHandle_t handle,
			   cublasOperation_t transa, cublasOperation_t transb,
			   int m, int n, int k,
			   const __half *alpha,
			   const __half *A, int lda,
			   const __half *B, int ldb,
			   const __half *beta,
			   __half *C, int ldc)
{
	for (int row = 0; row < m; ++row) {
		for (int col = 0; col < n; ++col) {
			__half sum = __float2half(0.0f);
			for (int i = 0; i < k; ++i) {
				float fA = __half2float(A[row + i * lda]);
				float fB = __half2float(B[i + col * ldb]);
				float fSum = fA * fB + __half2float(sum);
				sum = __float2half(fSum);
			}
			C[row + col * ldc] = (*alpha) * sum + (*beta) * C[row + col * ldc];
		}
	}
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasGemmEx(cublasHandle_t handle,
			    cublasOperation_t transa,
			    cublasOperation_t transb,
			    int m,
			    int n,
			    int k,
			    const void *alpha,
			    const void *A,
			    cudaDataType_t Atype,
			    int lda,
			    const void *B,
			    cudaDataType_t Btype,
			    int ldb,
			    const void *beta,
			    void *C,
			    cudaDataType_t Ctype,
			    int ldc,
			    cublasComputeType_t computeType,
			    cublasGemmAlgo_t algo)
{
	return CUBLAS_STATUS_SUCCESS;
}
