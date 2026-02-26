// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2025-2026 Rong Tao */
#ifndef __CUDA_ADAPTER_CUBLAS_API_H
#define __CUDA_ADAPTER_CUBLAS_API_H 1

#include "wrapper_defs.h"

#ifdef CUBLAS_API_H_
#error "CudaAdapter not allow include origin CUDA cublas_api.h"
#endif

/**
 * HIP: typedef void* hipblasHandle_t;
 */
#define cublasStatus_t cuX(blasStatus_t) /* enum */
#define CUBLAS_STATUS_SUCCESS CUX(BLAS_STATUS_SUCCESS)
#define CUBLAS_STATUS_NOT_INITIALIZED CUX(BLAS_STATUS_NOT_INITIALIZED)
#define CUBLAS_STATUS_ALLOC_FAILED CUX(BLAS_STATUS_ALLOC_FAILED)
#define CUBLAS_STATUS_INVALID_VALUE CUX(BLAS_STATUS_INVALID_VALUE)
#define CUBLAS_STATUS_ARCH_MISMATCH CUX(BLAS_STATUS_ARCH_MISMATCH)
#define CUBLAS_STATUS_MAPPING_ERROR CUX(BLAS_STATUS_MAPPING_ERROR)
#define CUBLAS_STATUS_EXECUTION_FAILED CUX(BLAS_STATUS_EXECUTION_FAILED)
#define CUBLAS_STATUS_INTERNAL_ERROR CUX(BLAS_STATUS_INTERNAL_ERROR)
#define CUBLAS_STATUS_NOT_SUPPORTED CUX(BLAS_STATUS_NOT_SUPPORTED)

#define cublasFillMode_t cuX(blasFillMode_t) /* enum */
#define CUBLAS_FILL_MODE_LOWER CUX(BLAS_FILL_MODE_LOWER)
#define CUBLAS_FILL_MODE_UPPER CUX(BLAS_FILL_MODE_UPPER)
#define CUBLAS_FILL_MODE_FULL CUX(BLAS_FILL_MODE_FULL)

#define cublasDiagType_t cuX(blasDiagType_t) /* enum */
#define CUBLAS_DIAG_NON_UNIT CUX(BLAS_DIAG_NON_UNIT)
#define CUBLAS_DIAG_UNIT CUX(BLAS_DIAG_UNIT)

#define cublasSideMode_t cuX(blasSideMode_t) /* enum */
#define CUBLAS_SIDE_LEFT CUX(BLAS_SIDE_LEFT)
#define CUBLAS_SIDE_RIGHT CUX(BLAS_SIDE_RIGHT)

/**
 * The cublasOperation_t type indicates which operation needs to be performed
 * with the dense matrix.
 */
#define cublasOperation_t cuX(blasOperation_t)
/* The non-transpose operation is selected. */
#define CUBLAS_OP_N CUX(BLAS_OP_N)
/* The transpose operation is selected. */
#define CUBLAS_OP_T CUX(BLAS_OP_T)
/* The conjugate transpose operation is selected. */
#define CUBLAS_OP_C CUX(BLAS_OP_C)
#define CUBLAS_OP_HERMITAN CUX(BLAS_OP_HERMITAN)
#define CUBLAS_OP_CONJG CUX(BLAS_OP_CONJG)

/**
 * The cublasPointerMode_t type indicates whether the scalar values are passed
 * by reference on the host or device.
 */
#define cublasPointerMode_t cuX(blasPointerMode_t)
#define CUBLAS_POINTER_MODE_HOST CUX(BLAS_POINTER_MODE_HOST)
#define CUBLAS_POINTER_MODE_DEVICE CUX(BLAS_POINTER_MODE_DEVICE)

#define cublasAtomicsMode_t cuX(blasAtomicsMode_t) /* enum */
#define CUBLAS_ATOMICS_NOT_ALLOWED CUX(BLAS_ATOMICS_NOT_ALLOWED)
#define CUBLAS_ATOMICS_ALLOWED CUX(BLAS_ATOMICS_ALLOWED)

/**
 * cublasGemmAlgo_t type is an enumerant to specify the algorithm for
 * matrix-matrix multiplication.
 */
#define cublasGemmAlgo_t cuX(blasGemmAlgo_t) /* enum */
#define CUBLAS_GEMM_DEFAULT CUX(BLAS_GEMM_DEFAULT)
#define CUBLAS_GEMM_ALGO0 CUX(BLAS_GEMM_ALGO0)
#define CUBLAS_GEMM_ALGO1 CUX(BLAS_GEMM_ALGO1)
#define CUBLAS_GEMM_ALGO2 CUX(BLAS_GEMM_ALGO2)
#define CUBLAS_GEMM_ALGO3 CUX(BLAS_GEMM_ALGO3)
#define CUBLAS_GEMM_ALGO4 CUX(BLAS_GEMM_ALGO4)
#define CUBLAS_GEMM_ALGO5 CUX(BLAS_GEMM_ALGO5)
#define CUBLAS_GEMM_ALGO6 CUX(BLAS_GEMM_ALGO6)
#define CUBLAS_GEMM_ALGO7 CUX(BLAS_GEMM_ALGO7)
#define CUBLAS_GEMM_ALGO8 CUX(BLAS_GEMM_ALGO8)
#define CUBLAS_GEMM_ALGO9 CUX(BLAS_GEMM_ALGO9)
#define CUBLAS_GEMM_ALGO10 CUX(BLAS_GEMM_ALGO10)
#define CUBLAS_GEMM_ALGO11 CUX(BLAS_GEMM_ALGO11)
#define CUBLAS_GEMM_ALGO12 CUX(BLAS_GEMM_ALGO12)
#define CUBLAS_GEMM_ALGO13 CUX(BLAS_GEMM_ALGO13)
#define CUBLAS_GEMM_ALGO14 CUX(BLAS_GEMM_ALGO14)
#define CUBLAS_GEMM_ALGO15 CUX(BLAS_GEMM_ALGO15)
#define CUBLAS_GEMM_ALGO16 CUX(BLAS_GEMM_ALGO16)
#define CUBLAS_GEMM_ALGO17 CUX(BLAS_GEMM_ALGO17)
#define CUBLAS_GEMM_ALGO18 CUX(BLAS_GEMM_ALGO18)
#define CUBLAS_GEMM_ALGO19 CUX(BLAS_GEMM_ALGO19)
#define CUBLAS_GEMM_ALGO20 CUX(BLAS_GEMM_ALGO20)
#define CUBLAS_GEMM_ALGO21 CUX(BLAS_GEMM_ALGO21)
#define CUBLAS_GEMM_ALGO22 CUX(BLAS_GEMM_ALGO22)
#define CUBLAS_GEMM_ALGO23 CUX(BLAS_GEMM_ALGO23)
#define CUBLAS_GEMM_DEFAULT_TENSOR_OP CUX(BLAS_GEMM_DEFAULT_TENSOR_OP)
#define CUBLAS_GEMM_ALGO0_TENSOR_OP CUX(BLAS_GEMM_ALGO0_TENSOR_OP)
#define CUBLAS_GEMM_ALGO1_TENSOR_OP CUX(BLAS_GEMM_ALGO1_TENSOR_OP)
#define CUBLAS_GEMM_ALGO2_TENSOR_OP CUX(BLAS_GEMM_ALGO2_TENSOR_OP)
#define CUBLAS_GEMM_ALGO3_TENSOR_OP CUX(BLAS_GEMM_ALGO3_TENSOR_OP)
#define CUBLAS_GEMM_ALGO4_TENSOR_OP CUX(BLAS_GEMM_ALGO4_TENSOR_OP)
#define CUBLAS_GEMM_ALGO5_TENSOR_OP CUX(BLAS_GEMM_ALGO5_TENSOR_OP)
#define CUBLAS_GEMM_ALGO6_TENSOR_OP CUX(BLAS_GEMM_ALGO6_TENSOR_OP)
#define CUBLAS_GEMM_ALGO7_TENSOR_OP CUX(BLAS_GEMM_ALGO7_TENSOR_OP)
#define CUBLAS_GEMM_ALGO8_TENSOR_OP CUX(BLAS_GEMM_ALGO8_TENSOR_OP)
#define CUBLAS_GEMM_ALGO9_TENSOR_OP CUX(BLAS_GEMM_ALGO9_TENSOR_OP)
#define CUBLAS_GEMM_ALGO10_TENSOR_OP CUX(BLAS_GEMM_ALGO10_TENSOR_OP)
#define CUBLAS_GEMM_ALGO11_TENSOR_OP CUX(BLAS_GEMM_ALGO11_TENSOR_OP)
#define CUBLAS_GEMM_ALGO12_TENSOR_OP CUX(BLAS_GEMM_ALGO12_TENSOR_OP)
#define CUBLAS_GEMM_ALGO13_TENSOR_OP CUX(BLAS_GEMM_ALGO13_TENSOR_OP)
#define CUBLAS_GEMM_ALGO14_TENSOR_OP CUX(BLAS_GEMM_ALGO14_TENSOR_OP)
#define CUBLAS_GEMM_ALGO15_TENSOR_OP CUX(BLAS_GEMM_ALGO15_TENSOR_OP)
#define CUBLAS_GEMM_AUTOTUNE CUX(BLAS_GEMM_AUTOTUNE)

#define cublasMath_t cuX(blasMath_t) /* enum */

/**
 * typedef cudaDataType cublasDataType_t;
 */
#define cublasDataType_t cuX(blasDataType_t)

/**
 * cublasComputeType_t enumerate type is used in cublasGemmEx() and
 * cublasLtMatmul() (including all batched and strided batched variants) to
 * choose compute precision modes as defined below.
 */
#define cublasComputeType_t cuX(blasComputeType_t)
/**
 * This is the default and highest-performance mode for 16-bit half precision
 * floating point and all compute and intermediate storage precisions with at
 * least 16-bit half precision. Tensor Cores will be used whenever possible.
 */
#define CUBLAS_COMPUTE_16F CUX(BLAS_COMPUTE_16F)
/**
 * This mode uses 16-bit half precision floating point standardized arithmetic
 * for all phases of calculations and is primarily intended for numerical
 * robustness studies, testing, and debugging. This mode might not be as
 * performant as the other modes since it disables use of tensor cores.
 */
#define CUBLAS_COMPUTE_16F_PEDANTIC CUX(BLAS_COMPUTE_16F_PEDANTIC)
/**
 * This is the default 32-bit single precision floating point and uses compute
 * and intermediate storage precisions of at least 32-bits.
 */
#define CUBLAS_COMPUTE_32F CUX(BLAS_COMPUTE_32F)
#define CUBLAS_COMPUTE_32F_PEDANTIC CUX(BLAS_COMPUTE_32F_PEDANTIC)
/**
 * Allows the library to use Tensor Cores with automatic down-conversion and
 * 16-bit half-precision compute for 32-bit input and output matrices.
 */
#define CUBLAS_COMPUTE_32F_FAST_16F CUX(BLAS_COMPUTE_32F_FAST_16F)
#define CUBLAS_COMPUTE_32F_FAST_16BF CUX(BLAS_COMPUTE_32F_FAST_16BF)
#define CUBLAS_COMPUTE_32F_FAST_TF32 CUX(BLAS_COMPUTE_32F_FAST_TF32)
#define CUBLAS_COMPUTE_32F_EMULATED_16BFX9 CUX(BLAS_COMPUTE_32F_EMULATED_16BFX9)
/**
 * This is the default 64-bit double precision floating point and uses compute
 * and intermediate storage precisions of at least 64-bits.
 */
#define CUBLAS_COMPUTE_64F CUX(BLAS_COMPUTE_64F)
#define CUBLAS_COMPUTE_64F_PEDANTIC CUX(BLAS_COMPUTE_64F_PEDANTIC)
/**
 * This is the default 32-bit integer mode and uses compute and intermediate
 * storage precisions of at least 32-bits.
 */
#define CUBLAS_COMPUTE_32I CUX(BLAS_COMPUTE_32I)
#define CUBLAS_COMPUTE_32I_PEDANTIC CUX(BLAS_COMPUTE_32I_PEDANTIC)

#define cublasEmulationStrategy_t cuX(blasEmulationStrategy_t) /* enum */

/**
 * typedef struct cublasContext* cublasHandle_t;
 */
#define cublasHandle_t cuX(blasHandle_t)

#define cublasLogCallback cuX(blasLogCallback)

#endif
