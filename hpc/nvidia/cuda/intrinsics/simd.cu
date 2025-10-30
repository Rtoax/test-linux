// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * https://docs.nvidia.com/cuda/cuda-math-api/cuda_math_api/group__CUDA__MATH__INTRINSIC__SIMD.html
 */
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "cuda_compat.h"
#include "compiler.h"
#include "print.h"
#include "types.h"


__global__ void k_simd_types(void)
{
	short2 s;
	s.x = 1;
	s.y = 2;
	PSHORT2(s);
}

#define UINT16x2toUINT32(s1, s2) ({	\
		unsigned short __s1 = (unsigned short)s1;	\
		unsigned short __s2 = (unsigned short)s2;	\
		unsigned int __v = __s1 << 16 | __s2;	\
		__v;	\
	})

#define UINT8x4toUINT32(u1, u2, u3, u4) ({	\
		uint8_t __u1 = (uint8_t)u1;	\
		uint8_t __u2 = (uint8_t)u2;	\
		uint8_t __u3 = (uint8_t)u3;	\
		uint8_t __u4 = (uint8_t)u4;	\
		unsigned int __v = __u1 << 24 | __u2 << 16 | __u3 << 8 | __u4;	\
		__v;	\
	})

__global__ void k_simd_abs2(void)
{
#if !defined(__HIPCC__)
	unsigned int input = UINT16x2toUINT32(-123, 456);
	unsigned int result = __vabs2(input);

	short2 input_short2 = *reinterpret_cast<short2 *>(&input);
	short2 result_short2 = *reinterpret_cast<short2 *>(&result);

	PUINT32toINT16x2(input);
	PUINT32toINT16x2(result);
	PSHORT2(input_short2);
	PSHORT2(result_short2);
#endif
}

__global__ void k_simd_u8x4(void)
{
#if !defined(__HIPCC__)
	unsigned int input = UINT8x4toUINT32(-1, -2, -3, -4);
	PUINT32toINT8x4(input);
	PUINT32toINT8x4(__vabs4(input));
#endif
}

int main(int argc, char *argv[])
{
	k_simd_types<<<1, 1>>>();

	k_simd_abs2<<<1, 1>>>();
	k_simd_u8x4<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
