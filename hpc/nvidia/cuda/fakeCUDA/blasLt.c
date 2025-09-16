#include <cuda.h>
#include <cuda_runtime.h>
#include <cublas.h>
#include <cublasLt.h>
#include <math.h>
#include <string.h>
#include "debug.h"
#include "types.h"


cublasStatus_t cublasLtCreate(cublasLtHandle_t *lighthandle)
{
	return CUBLAS_STATUS_SUCCESS;
}

cublasStatus_t cublasLtDestroy(cublasLtHandle_t lightHandle)
{
	return CUBLAS_STATUS_SUCCESS;
}
