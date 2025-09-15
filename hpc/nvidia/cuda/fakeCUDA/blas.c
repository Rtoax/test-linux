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
