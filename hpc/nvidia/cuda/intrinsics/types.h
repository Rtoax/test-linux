#pragma once

#define PI_FLOAT	3.141592653f
#define PI_DOUBLE	3.141592653

#define USHORT_INF_FP16		0x7C00U
#define USHORT_MAX_NORMAL_FP16	0x7BFFU
#define USHORT_MIN_DENORM_FP16	0x0001U
#define USHORT_NAN_FP16		0x7FFFU
#define USHORT_NEG_ZERO_FP16	0x8000U
#define USHORT_ZERO_FP16	0x0000U
#define USHORT_ONE_FP16		0x3C00U
#define USHORT_TWO_FP16		0x4000U

#define USHORT_INF_BF16		0x7F80U
#define USHORT_MAX_NORMAL_BF16	0x7F7FU
#define USHORT_MIN_DENORM_BF16	0x0001U
#define USHORT_NAN_BF16		0x7FFFU
#define USHORT_NEG_ZERO_BF16	0x8000U
#define USHORT_ONE_BF16		0x3F80U
#define USHORT_ZERO_BF16	0x0000U

#if !defined(__NVCC__) || (defined(CUDA_VERSION) && CUDA_VERSION < 12000)
/**
 * Half Arithmetic Constants
 * https://docs.nvidia.com/cuda/cuda-math-api/cuda_math_api/group__CUDA__MATH__INTRINSIC__HALF__PHALFS.html
 */
#define CUDART_INF_FP16 __ushort_as_half((unsigned short)USHORT_INF_FP16)
#define CUDART_MAX_NORMAL_FP16 __ushort_as_half((unsigned short)USHORT_MAX_NORMAL_FP16)
#define CUDART_MIN_DENORM_FP16 __ushort_as_half((unsigned short)USHORT_MIN_DENORM_FP16)
#define CUDART_NAN_FP16 __ushort_as_half((unsigned short)USHORT_NAN_FP16)
#define CUDART_NEG_ZERO_FP16 __ushort_as_half((unsigned short)USHORT_NEG_ZERO_FP16)
#define CUDART_ZERO_FP16 __ushort_as_half((unsigned short)USHORT_ZERO_FP16)
#define CUDART_ONE_FP16 __ushort_as_half((unsigned short)USHORT_ONE_FP16)

/**
 * Bfloat16 Arithmetic Constants
 * https://docs.nvidia.com/cuda/cuda-math-api/cuda_math_api/group__CUDA__MATH__INTRINSIC__BFLOAT16__CONSTANTS.html
 */
#define CUDART_INF_BF16	__ushort_as_bfloat16((unsigned short)USHORT_INF_BF16)
#define CUDART_MAX_NORMAL_BF16	__ushort_as_bfloat16((unsigned short)USHORT_MAX_NORMAL_BF16)
#define CUDART_MIN_DENORM_BF16	__ushort_as_bfloat16((unsigned short)USHORT_MIN_DENORM_BF16)
#define CUDART_NAN_BF16	__ushort_as_bfloat16((unsigned short)USHORT_NAN_BF16)
#define CUDART_NEG_ZERO_BF16	__ushort_as_bfloat16((unsigned short)USHORT_NEG_ZERO_BF16)
#define CUDART_ONE_BF16	__ushort_as_bfloat16((unsigned short)USHORT_ONE_BF16)
#define CUDART_ZERO_BF16	__ushort_as_bfloat16((unsigned short)USHORT_ZERO_BF16)
#endif
