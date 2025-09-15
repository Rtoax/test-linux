#include <cuda.h>
#include <cuda_runtime.h>
#include <cublas.h>


cublasStatus_t cublasCreate_v2(cublasHandle_t *handle)
{
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasDestroy_v2(cublasHandle_t handle)
{
	return CUBLAS_STATUS_SUCCESS;
}
