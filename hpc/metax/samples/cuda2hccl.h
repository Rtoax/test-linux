// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Metax has CUDA-compatible APIs */
#pragma once

/* typedef hcError_t	cudaError_t; */
#define cudaError_t	hcError_t
#define cudaSuccess	hcSuccess
#define cudaErrorInvalidValue	hcErrorInvalidValue
#define cudaErrorMemoryAllocation	hcErrorMemoryAllocation

#define cudaGetLastError()	hcGetLastError()
#define cudaGetErrorString(err)	hcGetErrorString(err)

#define cudaDeviceSetLimit(limit, value)	hcDeviceSetLimit(limit, value)
#define cudaLimitPrintfFifoSize	hcLimitPrintfFifoSize

#define cudaMalloc(pp, sz)	hcMalloc(pp, sz)
#define cudaFree(ptr)	hcFree(ptr)
#define cudaMemset(ptr, v, size)	hcMemset(ptr, v, size)
#define cudaMemcpy(dev, host, size, flag)	hcMemcpy(dev, host, size, flag)
#define cudaMemcpyHostToDevice	hcMemcpyHostToDevice
#define cudaMemcpyDeviceToHost	hcMemcpyDeviceToHost

#define cudaEvent_t	hcEvent_t
#define cudaEventCreate(pe)	hcEventCreate(pe)
#define cudaEventDestroy(ev)	hcEventDestroy(ev)
#define cudaEventRecord(ev)	hcEventRecord(ev)
#define cudaEventElapsedTime(pt, start, stop)	hcEventElapsedTime(pt, start, stop)
/**
 * cudaEventSynchronize() will block the CPU until the CPU waits for the GPU
 * calculation to complete the event 'ev'.
 */
#define cudaEventSynchronize(ev)	hcEventSynchronize(ev)

/**
 * cudaStream_t is a data type in CUDA used to represent a stream. A stream in
 * CUDA is a sequence of operations (such as kernel launches or memory
 * transfers) that execute in order on the GPU. Streams enable asynchronous
 * execution, allowing multiple operations to overlap and improve performance
 * by utilizing GPU resources more efficiently.
 */
#define cudaStream_t	hcStream_t
#define cudaStreamCreate(pstream)	hcStreamCreate(pstream)
#define cudaStreamSynchronize(stream)	hcStreamSynchronize(stream)
#define cudaStreamDestroy(stream)	hcStreamDestroy(stream)

#define cudaGetDevice(p_id)	hcGetDevice(p_id)
#define cudaSetDevice(dev_id)	hcSetDevice(dev_id)

#define cudaDeviceProp	hcDeviceProp_t
#define cudaGetDeviceProperties(prop, devid)	hcGetDeviceProperties(prop, devid)

#define cudaDeviceGetAttribute(pval, attr, dev_id)	hcDeviceGetAttribute(pval, attr, dev_id)
#define cudaDevAttrClockRate	hcDevAttrClockRate
#define cudaDevAttrMaxThreadsPerMultiProcessor	hcDevAttrMaxThreadsPerMultiProcessor

#define cudaDeviceGetP2PAttribute(v, attr, src, dst)	hcDeviceGetP2PAttribute(v, attr, src, dst)
#define cudaDevP2PAttrPerformanceRank	hcDevP2PAttrPerformanceRank
#define cudaDevP2PAttrAccessSupported	hcDevP2PAttrAccessSupported
#define cudaDevP2PAttrNativeAtomicSupported	hcDevP2PAttrNativeAtomicSupported

#define cudaDeviceSynchronize()	hcDeviceSynchronize()

/**
 * BLAS: Basic Linear Algebra Subprograms
 * see /usr/local/cuda-12.9/targets/x86_64-linux/include/cublas_api.h
 *
 * refs:
 * - https://docs.nvidia.com/cuda/cublas/index.html
 */
#define cublasGetStatusString(status)	hcblasGetStatusString(status)
#define cublasStatus_t	hcblasStatus_t
#define CUBLAS_STATUS_SUCCESS	HCBLAS_STATUS_SUCCESS
#define CUBLAS_STATUS_NOT_INITIALIZED	HCBLAS_STATUS_NOT_INITIALIZED
#define CUBLAS_STATUS_ALLOC_FAILED	HCBLAS_STATUS_ALLOC_FAILED
#define CUBLAS_STATUS_INVALID_VALUE	HCBLAS_STATUS_INVALID_VALUE
#define CUBLAS_STATUS_ARCH_MISMATCH	HCBLAS_STATUS_ARCH_MISMATCH
#define CUBLAS_STATUS_MAPPING_ERROR	HCBLAS_STATUS_MAPPING_ERROR
#define CUBLAS_STATUS_EXECUTION_FAILED	HCBLAS_STATUS_EXECUTION_FAILED
#define CUBLAS_STATUS_INTERNAL_ERROR	HCBLAS_STATUS_INTERNAL_ERROR
#define CUBLAS_STATUS_NOT_SUPPORTED	HCBLAS_STATUS_NOT_SUPPORTED

#define cublasHandle_t	hcblasHandle_t
#define cublasCreate(handle)	hcblasCreate(handle)
#define cublasDestroy(handle)	hcblasDestroy(handle)

#define cublasGetVersion(handle, pversion)	hcblasGetVersion(handle, pversion)
#define cublasGetProperty(type, pvalue)	hcblasGetProperty(type, pvalue)

/**
 * The cublasOperation_t type indicates which operation needs to be performed
 * with the dense matrix.
 */
#define cublasOperation_t	hcblasOperation_t
/* The non-transpose operation is selected. */
#define CUBLAS_OP_N	HCBLAS_OP_N
/* The transpose operation is selected. */
#define CUBLAS_OP_T	HCBLAS_OP_T
/* The conjugate transpose operation is selected. */
#define CUBLAS_OP_C	HCBLAS_OP_C
#define CUBLAS_OP_HERMITAN	HCBLAS_OP_HERMITAN
#define CUBLAS_OP_CONJG	HCBLAS_OP_CONJG

#define cublasFillMode_t	hcblasFillMode_t
#define CUBLAS_FILL_MODE_LOWER	HCBLAS_FILL_MODE_LOWER
#define CUBLAS_FILL_MODE_UPPER	HCBLAS_FILL_MODE_UPPER
#define CUBLAS_FILL_MODE_FULL	HCBLAS_FILL_MODE_FULL

#define cublasSetMatrix(rows, cols, elemsize, A, ola, B, ldb)	\
	hcblasSetMatrix(rows, cols, elemsize, A, ola, B, ldb)
#define cublasGetMatrix(rows, cols, elemsize, A, ola, B, ldb)	\
	hcblasGetMatrix(rows, cols, elemsize, A, ola, B, ldb)

#define cublasSetVector(n, elemSize, x, incx, y, incy) \
	hcblasSetVector(n, elemSize, x, incx, y, incy)
#define cublasGetVector(n, elemSize, x, incx, y, incy) \
	hcblasGetVector(n, elemSize, x, incx, y, incy)

/**
 * The cublasPointerMode_t type indicates whether the scalar values are passed
 * by reference on the host or device.
 */
#define cublasPointerMode_t	hcblasPointerMode_t
#define CUBLAS_POINTER_MODE_HOST	HCBLAS_POINTER_MODE_HOST
#define CUBLAS_POINTER_MODE_DEVICE	HCBLAS_POINTER_MODE_DEVICE

#define cublasGetPointerMode(handle, mode)	hcblasGetPointerMode(handle, mode)
#define cublasSetPointerMode(handle, mode)	hcblasSetPointerMode(handle, mode)

/**
 * x[j] = alpha * x[j]
 * i = 1 ... n
 * j = 1 + (i − 1) * incx
 *
 * S-float, D-double, C-Complex, Cs-Complex/float, Z-DoubleComplex, Zd-DoubleComplex/double
 */
#define cublasSscal(handle, n, alpha, x, incx)	hcblasSscal(handle, n, alpha, x, incx)
#define cublasDscal(handle, n, alpha, x, incx)	hcblasDscal(handle, n, alpha, x, incx)
#define cublasCscal(handle, n, alpha, x, incx)	hcblasCscal(handle, n, alpha, x, incx)
#define cublasCsscal(handle, n, alpha, x, incx)	hcblasCsscal(handle, n, alpha, x, incx)
#define cublasZscal(handle, n, alpha, x, incx)	hcblasZscal(handle, n, alpha, x, incx)
#define cublasZdscal(handle, n, alpha, x, incx)	hcblasZdscal(handle, n, alpha, x, incx)

/**
 * This function finds the (smallest) index of the element of the maximum
 * magnitude.
 */
#define cublasIsamax(handle, n, x, incx, presult)	hcblasIsamax(handle, n, x, incx, presult)
#define cublasIdamax(handle, n, x, incx, presult)	hcblasIdamax(handle, n, x, incx, presult)
#define cublasIcamax(handle, n, x, incx, presult)	hcblasIcamax(handle, n, x, incx, presult)
#define cublasIzamax(handle, n, x, incx, presult)	hcblasIzamax(handle, n, x, incx, presult)

/**
 * This function finds the (smallest) index of the element of the minimum
 * magnitude.
 */
#define cublasIsamin(handle, n, x, incx, presult)	hcblasIsamin(handle, n, x, incx, presult)
#define cublasIdamin(handle, n, x, incx, presult)	hcblasIdamin(handle, n, x, incx, presult)
#define cublasIcamin(handle, n, x, incx, presult)	hcblasIcamin(handle, n, x, incx, presult)
#define cublasIzamin(handle, n, x, incx, presult)	hcblasIzamin(handle, n, x, incx, presult)

/**
 * This function computes the sum of the absolute values of the elements of
 * vector x.
 */
#define cublasSasum(handle, n, x, incx, presult)	hcblasSasum(handle, n, x, incx, presult)
#define cublasDasum(handle, n, x, incx, presult)	hcblasDasum(handle, n, x, incx, presult)
#define cublasScasum(handle, n, x, incx, presult)	hcblasScasum(handle, n, x, incx, presult)
#define cublasDzasum(handle, n, x, incx, presult)	hcblasDzasum(handle, n, x, incx, presult)

/**
 * This function multiplies the vector x by the scalar alpha and adds it to
 * the vector y overwriting the latest vector with the result.
 *
 * y[j] = alpha x x[k] + y[j]
 * i = 1, ..., n
 * k = 1 + (i − 1) * incx
 * j = 1 + (i − 1) * incy
 */
#define cublasSaxpy(handle, n, alpha, x, incx, y, incy)	hcblasSaxpy(handle, n, alpha, x, incx, y, incy)
#define cublasDaxpy(handle, n, alpha, x, incx, y, incy)	hcblasDaxpy(handle, n, alpha, x, incx, y, incy)
#define cublasCaxpy(handle, n, alpha, x, incx, y, incy)	hcblasCaxpy(handle, n, alpha, x, incx, y, incy)
#define cublasZaxpy(handle, n, alpha, x, incx, y, incy)	hcblasZaxpy(handle, n, alpha, x, incx, y, incy)

/**
 * This function copies the vector x into the vector y.
 *
 * y[j] = x[k]
 * i = 1, ..., n
 * k = 1 + (i − 1) * incx
 * j = 1 + (i − 1) * incy
 */
#define cublasScopy(handle, n, x, incx, y, incy)	hcblasScopy(handle, n, x, incx, y, incy)
#define cublasDcopy(handle, n, x, incx, y, incy)	hcblasDcopy(handle, n, x, incx, y, incy)
#define cublasCcopy(handle, n, x, incx, y, incy)	hcblasCcopy(handle, n, x, incx, y, incy)
#define cublasZcopy(handle, n, x, incx, y, incy)	hcblasZcopy(handle, n, x, incx, y, incy)

/**
 * This function computes the dot product of vectors x and y.
 */
#define cublasSdot(handle, n, x, incx, y, incy, presult)	hcblasSdot(handle, n, x, incx, y, incy, presult)
#define cublasDdot(handle, n, x, incx, y, incy, presult)	hcblasDdot(handle, n, x, incx, y, incy, presult)
#define cublasCdotu(handle, n, x, incx, y, incy, presult)	hcblasCdotu(handle, n, x, incx, y, incy, presult)
#define cublasCdotc(handle, n, x, incx, y, incy, presult)	hcblasCdotc(handle, n, x, incx, y, incy, presult)
#define cublasZdotu(handle, n, x, incx, y, incy, presult)	hcblasZdotu(handle, n, x, incx, y, incy, presult)
#define cublasZdotc(handle, n, x, incx, y, incy, presult)	hcblasZdotc(handle, n, x, incx, y, incy, presult)

/**
 * This function computes the Euclidean norm of the vector x.
 */
#define cublasSnrm2(handle, n, x, incx, presult)	hcblasSnrm2(handle, n, x, incx, presult)
#define cublasDnrm2(handle, n, x, incx, presult)	hcblasDnrm2(handle, n, x, incx, presult)
#define cublasScnrm2(handle, n, x, incx, presult)	hcblasScnrm2(handle, n, x, incx, presult)
#define cublasDznrm2(handle, n, x, incx, presult)	hcblasDznrm2(handle, n, x, incx, presult)

/**
 * This function applies Givens rotation matrix.
 */
#define cublasSrot(handle, n, x, incx, y, incy, c, s)	hcblasSrot(handle, n, x, incx, y, incy, c, s)
#define cublasDrot(handle, n, x, incx, y, incy, c, s)	hcblasDrot(handle, n, x, incx, y, incy, c, s)
#define cublasCrot(handle, n, x, incx, y, incy, c, s)	hcblasCrot(handle, n, x, incx, y, incy, c, s)
#define cublasCsrot(handle, n, x, incx, y, incy, c, s)	hcblasCsrot(handle, n, x, incx, y, incy, c, s)
#define cublasZrot(handle, n, x, incx, y, incy, c, s)	hcblasZrot(handle, n, x, incx, y, incy, c, s)
#define cublasZdrot(handle, n, x, incx, y, incy, c, s)	hcblasZdrot(handle, n, x, incx, y, incy, c, s)

/**
 * This function constructs the Givens rotation matrix.
 */
#define cublasSrotg(handle, a, b, c, s)	hcblasSrotg(handle, a, b, c, s)
#define cublasDrotg(handle, a, b, c, s)	hcblasDrotg(handle, a, b, c, s)
#define cublasCrotg(handle, a, b, c, s)	hcblasCrotg(handle, a, b, c, s)
#define cublasZrotg(handle, a, b, c, s)	hcblasZrotg(handle, a, b, c, s)

#define cublasSrotm(handle, n, x, incx, y, incy, param)	hcblasSrotm(handle, n, x, incx, y, incy, param)
#define cublasDrotm(handle, n, x, incx, y, incy, param)	hcblasDrotm(handle, n, x, incx, y, incy, param)

/**
 * This function performs the matrix-matrix multiplication.
 *
 * C = alpha op(A) op(B) + beta C
 */
#define cublasSgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
	hcblasSgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc)
#define cublasDgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
	hcblasDgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc)
#define cublasCgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
	hcblasCgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc)
#define cublasZgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
	hcblasZgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc)
#define cublasHgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc) \
	hcblasHgemm(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc)

#define cublasLtHandle_t	hcblasLtHandle_t
#define cublasLtCreate(phandle)	hcblasLtCreate(phandle)
#define cublasLtDestroy(handle)	hcblasLtDestroy(handle)

#define cublasLtMatmulDesc_t	hcblasLtMatmulDesc_t
#define cublasLtMatmulDescCreate(pdesc, computeType, scaleType) \
	hcblasLtMatmulDescCreate(pdesc, computeType, scaleType)
#define cublasLtMatmulDescDestroy(desc)	hcblasLtMatmulDescDestroy(desc)

#define cublasLtMatmulDescAttributes_t	hcblasLtMatmulDescAttributes_t
#define CUBLASLT_MATMUL_DESC_COMPUTE_TYPE	HCBLASLT_MATMUL_DESC_COMPUTE_TYPE
#define CUBLASLT_MATMUL_DESC_SCALE_TYPE		HCBLASLT_MATMUL_DESC_SCALE_TYPE
#define CUBLASLT_MATMUL_DESC_POINTER_MODE	HCBLASLT_MATMUL_DESC_POINTER_MODE
/* more ... */

#define cublasLtMatmulHeuristicResult_t	hcblasLtMatmulHeuristicResult_t

#define cublasLtMatrixLayout_t	hcblasLtMatrixLayout_t
#define cublasLtMatrixLayoutCreate(playout, type, rows, cols, ld) \
	hcblasLtMatrixLayoutCreate(playout, type, rows, cols, ld)
#define cublasLtMatrixLayoutDestroy(layout)	hcblasLtMatrixLayoutDestroy(layout)

#define cublasLtMatrixLayoutAttribute_t	hcblasLtMatrixLayoutAttribute_t

#define cublasLtMatrixLayoutGetAttribute(matLayout, attr, buf, sizeInBytes, sizeWritten) \
	hcblasLtMatrixLayoutGetAttribute(matLayout, attr, buf, sizeInBytes, sizeWritten)

#define CUBLASLT_MATRIX_LAYOUT_ROWS	HCBLASLT_MATRIX_LAYOUT_ROWS
#define CUBLASLT_MATRIX_LAYOUT_COLS	HCBLASLT_MATRIX_LAYOUT_COLS
#define CUBLASLT_MATRIX_LAYOUT_LD	HCBLASLT_MATRIX_LAYOUT_LD
#define CUBLASLT_MATRIX_LAYOUT_TYPE	HCBLASLT_MATRIX_LAYOUT_TYPE

#define cublasLtMatmulAlgo_t	hcblasLtMatmulAlgo_t
#define CUBLASLT_ALGO_CAP_SPLITK_SUPPORT	HCBLASLT_ALGO_CAP_SPLITK_SUPPORT
#define CUBLASLT_ALGO_CAP_REDUCTION_SCHEME_MASK	HCBLASLT_ALGO_CAP_REDUCTION_SCHEME_MASK
#define CUBLASLT_ALGO_CAP_CTA_SWIZZLING_SUPPORT	HCBLASLT_ALGO_CAP_CTA_SWIZZLING_SUPPORT
#define CUBLASLT_ALGO_CAP_STRIDED_BATCH_SUPPORT	HCBLASLT_ALGO_CAP_STRIDED_BATCH_SUPPORT
#define CUBLASLT_ALGO_CAP_OUT_OF_PLACE_RESULT_SUPPORT	HCBLASLT_ALGO_CAP_OUT_OF_PLACE_RESULT_SUPPORT
#define CUBLASLT_ALGO_CAP_UPLO_SUPPORT	HCBLASLT_ALGO_CAP_UPLO_SUPPORT
#define CUBLASLT_ALGO_CAP_TILE_IDS	HCBLASLT_ALGO_CAP_TILE_IDS
#define CUBLASLT_ALGO_CAP_CUSTOM_OPTION_MAX	HCBLASLT_ALGO_CAP_CUSTOM_OPTION_MAX
#define CUBLASLT_ALGO_CAP_CUSTOM_MEMORY_ORDER	HCBLASLT_ALGO_CAP_CUSTOM_MEMORY_ORDER
#define CUBLASLT_ALGO_CAP_POINTER_MODE_MASK	HCBLASLT_ALGO_CAP_POINTER_MODE_MASK
#define CUBLASLT_ALGO_CAP_EPILOGUE_MASK	HCBLASLT_ALGO_CAP_EPILOGUE_MASK
#define CUBLASLT_ALGO_CAP_STAGES_IDS	HCBLASLT_ALGO_CAP_STAGES_IDS
#define CUBLASLT_ALGO_CAP_LD_NEGATIVE	HCBLASLT_ALGO_CAP_LD_NEGATIVE
#define CUBLASLT_ALGO_CAP_NUMERICAL_IMPL_FLAGS	HCBLASLT_ALGO_CAP_NUMERICAL_IMPL_FLAGS
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_A_BYTES	HCBLASLT_ALGO_CAP_MIN_ALIGNMENT_A_BYTES
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_B_BYTES	HCBLASLT_ALGO_CAP_MIN_ALIGNMENT_B_BYTES
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_C_BYTES	HCBLASLT_ALGO_CAP_MIN_ALIGNMENT_C_BYTES
#define CUBLASLT_ALGO_CAP_MIN_ALIGNMENT_D_BYTES	HCBLASLT_ALGO_CAP_MIN_ALIGNMENT_D_BYTES
#define CUBLASLT_ALGO_CAP_ATOMIC_SYNC	HCBLASLT_ALGO_CAP_ATOMIC_SYNC

#define cublasLtMatmulAlgoGetHeuristic(ltHandle, matmulDesc, layoutA, layoutB, \
				       layoutC, layoutD, pref, n, heuristic_result, rslt) \
	hcblasLtMatmulAlgoGetHeuristic(ltHandle, matmulDesc, layoutA, layoutB, \
				       layoutC, layoutD, pref, n, heuristic_result, rslt)
#define cublasLtMatmulPreferenceDestroy(pref)	hcblasLtMatmulPreferenceDestroy(pref)

#define cublasLtMatmulPreference_t	hcblasLtMatmulPreference_t
#define cublasLtMatmulPreferenceCreate(preference)	hcblasLtMatmulPreferenceCreate(preference)

#define CUBLASLT_MATMUL_PREF_MAX_WORKSPACE_BYTES	HCBLASLT_MATMUL_PREF_MAX_WORKSPACE_BYTES

/**
 * D = alpha*(A*B) + beta*(C)
 */
#define cublasLtMatmul(lightHandle, computeDesc, alpha, A, Adesc, B, Bdesc, \
		       beta, C, Cdesc, D, Ddesc, algo, workspace, \
		       workspaceSizeInBytes, stream) \
	hcblasLtMatmul(lightHandle, computeDesc, alpha, A, Adesc, B, Bdesc, \
		       beta, C, Cdesc, D, Ddesc, algo, workspace, \
		       workspaceSizeInBytes, stream)

/**
 * cublasGemmAlgo_t type is an enumerant to specify the algorithm for
 * matrix-matrix multiplication.
 */
#define cublasGemmAlgo_t	hcblasGemmAlgo_t
#define CUBLAS_GEMM_DEFAULT	HCBLAS_GEMM_DEFAULT
#define CUBLAS_GEMM_ALGO0	HCBLAS_GEMM_ALGO0
#define CUBLAS_GEMM_ALGO1	HCBLAS_GEMM_ALGO1
#define CUBLAS_GEMM_ALGO2	HCBLAS_GEMM_ALGO2
#define CUBLAS_GEMM_ALGO3	HCBLAS_GEMM_ALGO3
#define CUBLAS_GEMM_ALGO4	HCBLAS_GEMM_ALGO4
#define CUBLAS_GEMM_ALGO5	HCBLAS_GEMM_ALGO5
#define CUBLAS_GEMM_ALGO6	HCBLAS_GEMM_ALGO6
#define CUBLAS_GEMM_ALGO7	HCBLAS_GEMM_ALGO7
#define CUBLAS_GEMM_ALGO8	HCBLAS_GEMM_ALGO8
#define CUBLAS_GEMM_ALGO9	HCBLAS_GEMM_ALGO9
#define CUBLAS_GEMM_ALGO10	HCBLAS_GEMM_ALGO10
#define CUBLAS_GEMM_ALGO11	HCBLAS_GEMM_ALGO11
#define CUBLAS_GEMM_ALGO12	HCBLAS_GEMM_ALGO12
#define CUBLAS_GEMM_ALGO13	HCBLAS_GEMM_ALGO13
#define CUBLAS_GEMM_ALGO14	HCBLAS_GEMM_ALGO14
#define CUBLAS_GEMM_ALGO15	HCBLAS_GEMM_ALGO15
#define CUBLAS_GEMM_ALGO16	HCBLAS_GEMM_ALGO16
#define CUBLAS_GEMM_ALGO17	HCBLAS_GEMM_ALGO17
#define CUBLAS_GEMM_ALGO18	HCBLAS_GEMM_ALGO18
#define CUBLAS_GEMM_ALGO19	HCBLAS_GEMM_ALGO19
#define CUBLAS_GEMM_ALGO20	HCBLAS_GEMM_ALGO20
#define CUBLAS_GEMM_ALGO21	HCBLAS_GEMM_ALGO21
#define CUBLAS_GEMM_ALGO22	HCBLAS_GEMM_ALGO22
#define CUBLAS_GEMM_ALGO23	HCBLAS_GEMM_ALGO23
#define CUBLAS_GEMM_DEFAULT_TENSOR_OP	HCBLAS_GEMM_DEFAULT_TENSOR_OP
#define CUBLAS_GEMM_ALGO0_TENSOR_OP	CUBLAS_GEMM_ALGO0_TENSOR_OP
#define CUBLAS_GEMM_ALGO1_TENSOR_OP	CUBLAS_GEMM_ALGO1_TENSOR_OP
#define CUBLAS_GEMM_ALGO2_TENSOR_OP	CUBLAS_GEMM_ALGO2_TENSOR_OP
#define CUBLAS_GEMM_ALGO3_TENSOR_OP	CUBLAS_GEMM_ALGO3_TENSOR_OP
#define CUBLAS_GEMM_ALGO4_TENSOR_OP	CUBLAS_GEMM_ALGO4_TENSOR_OP
#define CUBLAS_GEMM_ALGO5_TENSOR_OP	CUBLAS_GEMM_ALGO5_TENSOR_OP
#define CUBLAS_GEMM_ALGO6_TENSOR_OP	CUBLAS_GEMM_ALGO6_TENSOR_OP
#define CUBLAS_GEMM_ALGO7_TENSOR_OP	CUBLAS_GEMM_ALGO7_TENSOR_OP
#define CUBLAS_GEMM_ALGO8_TENSOR_OP	CUBLAS_GEMM_ALGO8_TENSOR_OP
#define CUBLAS_GEMM_ALGO9_TENSOR_OP	CUBLAS_GEMM_ALGO9_TENSOR_OP
#define CUBLAS_GEMM_ALGO10_TENSOR_OP	CUBLAS_GEMM_ALGO10_TENSOR_OP
#define CUBLAS_GEMM_ALGO11_TENSOR_OP	CUBLAS_GEMM_ALGO11_TENSOR_OP
#define CUBLAS_GEMM_ALGO12_TENSOR_OP	CUBLAS_GEMM_ALGO12_TENSOR_OP
#define CUBLAS_GEMM_ALGO13_TENSOR_OP	CUBLAS_GEMM_ALGO13_TENSOR_OP
#define CUBLAS_GEMM_ALGO14_TENSOR_OP	CUBLAS_GEMM_ALGO14_TENSOR_OP
#define CUBLAS_GEMM_ALGO15_TENSOR_OP	CUBLAS_GEMM_ALGO15_TENSOR_OP

/**
 * cublasComputeType_t enumerate type is used in cublasGemmEx() and
 * cublasLtMatmul() (including all batched and strided batched variants) to
 * choose compute precision modes as defined below.
 */
#define cublasComputeType_t	hcblasComputeType_t
#define CUBLAS_COMPUTE_16F	HCBLAS_COMPUTE_16F
#define CUBLAS_COMPUTE_16F_PEDANTIC	HCBLAS_COMPUTE_16F_PEDANTIC
#define CUBLAS_COMPUTE_32F	HCBLAS_COMPUTE_32F
#define CUBLAS_COMPUTE_32F_PEDANTIC	HCBLAS_COMPUTE_32F_PEDANTIC
#define CUBLAS_COMPUTE_32F_FAST_16F	HCBLAS_COMPUTE_32F_FAST_16F
#define CUBLAS_COMPUTE_32F_FAST_16BF	HCBLAS_COMPUTE_32F_FAST_16BF
#define CUBLAS_COMPUTE_32F_FAST_TF32	HCBLAS_COMPUTE_32F_FAST_TF32
#define CUBLAS_COMPUTE_32F_EMULATED_16BFX9	HCBLAS_COMPUTE_32F_EMULATED_16BFX9
#define CUBLAS_COMPUTE_64F	HCBLAS_COMPUTE_64F
#define CUBLAS_COMPUTE_64F_PEDANTIC	HCBLAS_COMPUTE_64F_PEDANTIC
#define CUBLAS_COMPUTE_32I	HCBLAS_COMPUTE_32I
#define CUBLAS_COMPUTE_32I_PEDANTIC	HCBLAS_COMPUTE_32I_PEDANTIC

/**
 * see /usr/local/cuda-12.9/targets/x86_64-linux/include/library_types.h
 */
#define cudaDataType_t	hpccDataType_t
#define cudaDataType	hpccDataType
#define CUDA_R_16F	HPCC_R_16F
#define CUDA_C_16F	HPCC_C_16F
#define CUDA_R_16BF	HPCC_R_16BF
#define CUDA_C_16BF	HPCC_C_16BF
#define CUDA_R_32F	HPCC_R_32F
#define CUDA_C_32F	HPCC_C_32F
#define CUDA_R_64F	HPCC_R_64F
#define CUDA_C_64F	HPCC_C_64F
#define CUDA_R_4I	HPCC_R_4I
#define CUDA_C_4I	HPCC_C_4I
#define CUDA_R_4U	HPCC_R_4U
#define CUDA_C_4U	HPCC_C_4U
#define CUDA_R_8I	HPCC_R_8I
#define CUDA_C_8I	HPCC_C_8I
#define CUDA_R_8U	HPCC_R_8U
#define CUDA_C_8U	HPCC_C_8U
#define CUDA_R_16I	HPCC_R_16I
#define CUDA_C_16I	HPCC_C_16I
#define CUDA_R_16U	HPCC_R_16U
#define CUDA_C_16U	HPCC_C_16U
#define CUDA_R_32I	HPCC_R_32I
#define CUDA_C_32I	HPCC_C_32I
#define CUDA_R_32U	HPCC_R_32U
#define CUDA_C_32U	HPCC_C_32U
#define CUDA_R_64I	HPCC_R_64I
#define CUDA_C_64I	HPCC_C_64I
#define CUDA_R_64U	HPCC_R_64U
#define CUDA_C_64U	HPCC_C_64U
#define CUDA_R_8F_E4M3	HPCC_R_8F_E4M3
#define CUDA_R_8F_UE4M3	HPCC_R_8F_UE4M3
#define CUDA_R_8F_E5M2	HPCC_R_8F_E5M2
#define CUDA_R_8F_UE8M0	HPCC_R_8F_UE8M0
#define CUDA_R_6F_E2M3	HPCC_R_6F_E2M3
#define CUDA_R_6F_E3M2	HPCC_R_6F_E3M2
#define CUDA_R_4F_E2M1	HPCC_R_4F_E2M1

/**
 * float - s, S, real single-precision
 * double - d, D, real double-precision
 * cuComplex - c, C, complex single-precision
 * cuDoubleComplex - z, Z, complex double-precision
 */
#define cuComplex	hcComplex
#define cuDoubleComplex	hcDoubleComplex

/**
 * refs
 * - https://docs.nvidia.com/cuda/curand/group__HOST.html
 */
#define curandGetVersion(version)	hcrandGetVersion(version)
