// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#ifndef __CUDA_ADAPTER_CUBLASLT_H
#define __CUDA_ADAPTER_CUBLASLT_H 1

#include "wrapper_defs.h"
#include "cublas_api.h"

#define cublasLtHandle_t __cu(blasLtHandle_t)

/**
 * CUDA: size_t CUBLASWINAPI cublasLtGetVersion(void);
 * HIP: hipblasStatus_t hipblasLtGetVersion(hipblasLtHandle_t handle, int* version);
 */
#ifdef __USE_HIP__
#define cublasLtGetVersion(handle, pv) __cu(blasLtGetVersion(handle, pv))
#else
#define cublasLtGetVersion() __cu(blasLtGetVersion())
#endif

/**
 * CUDA: cublasStatus_t cublasLtCreate(cublasLtHandle_t* lightHandle);
 * HIP: hipblasStatus_t hipblasLtCreate(hipblasLtHandle_t* handle);
 */
#define cublasLtCreate(phandle) __cu(blasLtCreate(phandle))
#define cublasLtDestroy(handle) __cu(blasLtDestroy(handle))

#define cublasLtMatmulDesc_t __cu(blasLtMatmulDesc_t)

/**
 * CUDA:
 * cublasStatus_t cublasLtMatmulDescCreate(cublasLtMatmulDesc_t *matmulDesc,
 *                                         cublasComputeType_t computeType,
 *                                         cudaDataType_t scaleType);
 *
 * HIP:
 * hipblasStatus_t hipblasLtMatmulDescCreate(hipblasLtMatmulDesc_t* matmulDesc,
 *                                           hipblasComputeType_t   computeType,
 *                                           hipDataType            scaleType);
 *
 * This function creates a matrix multiply descriptor by allocating the memory
 * needed to hold its opaque structure.
 */
#define cublasLtMatmulDescCreate(pdesc, computeType, scaleType) \
 __cu(blasLtMatmulDescCreate(pdesc, computeType, scaleType))
#define cublasLtMatmulDescDestroy(desc) __cu(blasLtMatmulDescDestroy(desc))

#define cublasLtMatmulDescAttributes_t __cu(blasLtMatmulDescAttributes_t)
#define CUBLASLT_MATMUL_DESC_COMPUTE_TYPE __CU(BLASLT_MATMUL_DESC_COMPUTE_TYPE)
#define CUBLASLT_MATMUL_DESC_SCALE_TYPE  __CU(BLASLT_MATMUL_DESC_SCALE_TYPE)
#define CUBLASLT_MATMUL_DESC_POINTER_MODE __CU(BLASLT_MATMUL_DESC_POINTER_MODE)
/* more ... */

#define cublasLtMatmulHeuristicResult_t __cu(blasLtMatmulHeuristicResult_t)

#define cublasLtMatrixLayout_t __cu(blasLtMatrixLayout_t)
/**
 * CUDA:
 * cublasStatus_t cublasLtMatrixLayoutCreate(cublasLtMatrixLayout_t* matLayout,
 *                                           cudaDataType type,
 *                                             uint64_t rows,  uint64_t cols, int64_t ld);
 *
 * HIP:
 * hipblasStatus_t hipblasLtMatrixLayoutCreate(hipblasLtMatrixLayout_t* matLayout,
 *                                             hipDataType type,
 *                                             uint64_t rows, uint64_t cols, int64_t ld);
 */
#define cublasLtMatrixLayoutCreate(playout, type, rows, cols, ld) \
 __cu(blasLtMatrixLayoutCreate(playout, type, rows, cols, ld))
#define cublasLtMatrixLayoutDestroy(layout) __cu(blasLtMatrixLayoutDestroy(layout))

#define cublasLtMatrixLayoutAttribute_t __cu(blasLtMatrixLayoutAttribute_t)

/**
 * cublasStatus_t cublasLtMatrixLayoutGetAttribute(cublasLtMatrixLayout_t matLayout,
 *                                                 cublasLtMatrixLayoutAttribute_t attr,
 *                                                 void* buf,
 *                                                 size_t sizeInBytes,
 *                                                 size_t* sizeWritten);
 */
#define cublasLtMatrixLayoutGetAttribute(matLayout, attr, buf, sizeInBytes, sizeWritten) \
 __cu(blasLtMatrixLayoutGetAttribute(matLayout, attr, buf, sizeInBytes, sizeWritten))

#define CUBLASLT_MATRIX_LAYOUT_ROWS __CU(BLASLT_MATRIX_LAYOUT_ROWS)
#define CUBLASLT_MATRIX_LAYOUT_COLS __CU(BLASLT_MATRIX_LAYOUT_COLS)
#define CUBLASLT_MATRIX_LAYOUT_LD __CU(BLASLT_MATRIX_LAYOUT_LD)
#define CUBLASLT_MATRIX_LAYOUT_TYPE __CU(BLASLT_MATRIX_LAYOUT_TYPE)

#define cublasLtMatmulAlgo_t __cu(blasLtMatmulAlgo_t)
#define CUBLASLT_ALGO_CAP_SPLITK_SUPPORT __CU(BLASLT_ALGO_CAP_SPLITK_SUPPORT)
#define CUBLASLT_ALGO_CAP_REDUCTION_SCHEME_MASK __CU(BLASLT_ALGO_CAP_REDUCTION_SCHEME_MASK)
#define CUBLASLT_ALGO_CAP_CTA_SWIZZLING_SUPPORT __CU(BLASLT_ALGO_CAP_CTA_SWIZZLING_SUPPORT)
#define CUBLASLT_ALGO_CAP_STRIDED_BATCH_SUPPORT __CU(BLASLT_ALGO_CAP_STRIDED_BATCH_SUPPORT)
#define CUBLASLT_ALGO_CAP_OUT_OF_PLACE_RESULT_SUPPORT __CU(BLASLT_ALGO_CAP_OUT_OF_PLACE_RESULT_SUPPORT)
#define CUBLASLT_ALGO_CAP_UPLO_SUPPORT __CU(BLASLT_ALGO_CAP_UPLO_SUPPORT)
#define CUBLASLT_ALGO_CAP_TILE_IDS __CU(BLASLT_ALGO_CAP_TILE_IDS)
#define CUBLASLT_ALGO_CAP_CUSTOM_OPTION_MAX __CU(BLASLT_ALGO_CAP_CUSTOM_OPTION_MAX)
#define CUBLASLT_ALGO_CAP_CUSTOM_MEMORY_ORDER __CU(BLASLT_ALGO_CAP_CUSTOM_MEMORY_ORDER)
#define CUBLASLT_ALGO_CAP_POINTER_MODE_MASK __CU(BLASLT_ALGO_CAP_POINTER_MODE_MASK)
#define CUBLASLT_ALGO_CAP_EPILOGUE_MASK __CU(BLASLT_ALGO_CAP_EPILOGUE_MASK)
#define CUBLASLT_ALGO_CAP_STAGES_IDS __CU(BLASLT_ALGO_CAP_STAGES_IDS)
#define CUBLASLT_ALGO_CAP_LD_NEGATIVE __CU(BLASLT_ALGO_CAP_LD_NEGATIVE)
#define CUBLASLT_ALGO_CAP_NUMERICAL_IMPL_FLAGS __CU(BLASLT_ALGO_CAP_NUMERICAL_IMPL_FLAGS)
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_A_BYTES __CU(BLASLT_ALGO_CAP_MIN_ALIGNMENT_A_BYTES)
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_B_BYTES __CU(BLASLT_ALGO_CAP_MIN_ALIGNMENT_B_BYTES)
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_C_BYTES __CU(BLASLT_ALGO_CAP_MIN_ALIGNMENT_C_BYTES)
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_D_BYTES __CU(BLASLT_ALGO_CAP_MIN_ALIGNMENT_D_BYTES)
#define CUBLASLT_ALGO_CAP_ATOMIC_SYNC __CU(BLASLT_ALGO_CAP_ATOMIC_SYNC)

/**
 * CUDA:
 * cublasStatus_t cublasLtMatmulAlgoGetHeuristic(cublasLtHandle_t lightHandle,
 *                                               cublasLtMatmulDesc_t operationDesc,
 *                                               cublasLtMatrixLayout_t Adesc,
 *                                               cublasLtMatrixLayout_t Bdesc,
 *                                               cublasLtMatrixLayout_t Cdesc,
 *                                               cublasLtMatrixLayout_t Ddesc,
 *                                               cublasLtMatmulPreference_t preference,
 *                                               int requestedAlgoCount,
 *                                               cublasLtMatmulHeuristicResult_t heuristicResultsArray[],
 *                                               int* returnAlgoCount);
 *
 * HIP:
 * hipblasStatus_t hipblasLtMatmulAlgoGetHeuristic(hipblasLtHandle_t                handle,
 *                                                 hipblasLtMatmulDesc_t            matmulDesc,
 *                                                 hipblasLtMatrixLayout_t          Adesc,
 *                                                 hipblasLtMatrixLayout_t          Bdesc,
 *                                                 hipblasLtMatrixLayout_t          Cdesc,
 *                                                 hipblasLtMatrixLayout_t          Ddesc,
 *                                                 hipblasLtMatmulPreference_t      pref,
 *                                                 int                              requestedAlgoCount,
 *                                                 hipblasLtMatmulHeuristicResult_t heuristicResultsArray[],
 *                                                 int*                             returnAlgoCount);
 */
#define cublasLtMatmulAlgoGetHeuristic(ltHandle, matmulDesc, layoutA, layoutB, \
           layoutC, layoutD, pref, n, heuristic_result, rslt) \
 __cu(blasLtMatmulAlgoGetHeuristic(ltHandle, matmulDesc, layoutA, layoutB, \
           layoutC, layoutD, pref, n, heuristic_result, rslt))
#define cublasLtMatmulPreferenceDestroy(pref) __cu(blasLtMatmulPreferenceDestroy(pref))

#define cublasLtMatmulPreference_t __cu(blasLtMatmulPreference_t)
#define cublasLtMatmulPreferenceCreate(preference) __cu(blasLtMatmulPreferenceCreate(preference))

#define cublasLtMatmulPreferenceAttributes_t __cu(blasLtMatmulPreferenceAttributes_t)
#define cublasLtMatmulPreferenceSetAttribute(pref, arg1, ptr, size) \
	__cu(blasLtMatmulPreferenceSetAttribute(pref, arg1, ptr, size))

#define CUBLASLT_MATMUL_PREF_MAX_WORKSPACE_BYTES __CU(BLASLT_MATMUL_PREF_MAX_WORKSPACE_BYTES)

/**
 * D = alpha*(A*B) + beta*(C)
 */
#define cublasLtMatmul(lightHandle, computeDesc, alpha, A, Adesc, B, Bdesc, \
         beta, C, Cdesc, D, Ddesc, algo, workspace, \
         workspaceSizeInBytes, stream) \
 __cu(blasLtMatmul(lightHandle, computeDesc, alpha, A, Adesc, B, Bdesc, \
         beta, C, Cdesc, D, Ddesc, algo, workspace, \
         workspaceSizeInBytes, stream))

#ifdef __USE_HPCC__
# include <hcblas/hcblasLt.h>
#elif defined(__USE_LUCA__)
# ifdef LUCA_PHASE_II_PROJECT
#  include <lcblas/lcblasLt.h>
# else
#  include <hcblas/hcblasLt.h>
# endif
#elif defined(__USE_HIP__)
# ifdef __USE_HIP_V2__
#  define HIPBLAS_V2
# endif
# define HIPBLAS_USE_HIP_HALF
# include <hipblaslt/hipblaslt.h>
#endif

#endif
