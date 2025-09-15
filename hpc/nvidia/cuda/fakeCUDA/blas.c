#include <cuda.h>
#include <cuda_runtime.h>
#include <cublas.h>
#include <string.h>


cublasStatus_t cublasCreate_v2(cublasHandle_t *handle)
{
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasDestroy_v2(cublasHandle_t handle)
{
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
