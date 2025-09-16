#include <cuda.h>
#include <cuda_runtime.h>
#include <cublas.h>
#include <string.h>
#include "debug.h"


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
	LOG_DEBUG("type %d\n", type);

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

/* TODO: _Float32 may not supported */
typedef _Float32 __half;

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
			__half sum = 0.0f;
			for (int i = 0; i < k; ++i) {
				sum += A[row + i * lda] * B[i + col * ldb];
			}
			C[row + col * ldc] = (*alpha) * sum + (*beta) * C[row + col * ldc];
		}
	}
	return CUBLAS_STATUS_SUCCESS;
}
