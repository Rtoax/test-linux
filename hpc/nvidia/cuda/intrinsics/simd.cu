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

__global__ void k_simd_u16x2(void)
{
#if !defined(__HIPCC__)
	unsigned int input = UINT16x2toUINT32(-123, 456);
	unsigned int input2 = UINT16x2toUINT32(1, 2);
	PUINT32toINT16x2(input);
	PUINT32toINT16x2(input2);
	PUINT32toSHORT2(__vabs2(input));
	PUINT32toSHORT2(__vabsdiffs2(input, input2));
	PUINT32toSHORT2(__vabsdiffu2(input, input2));
	PUINT32toSHORT2(__vabsss2(input));
	PUINT32toSHORT2(__vadd2(input, input2));
	PUINT32toSHORT2(__vaddss2(input, input2));
	PUINT32toSHORT2(__vaddus2(input, input2));
	PUINT32toSHORT2(__vavgs2(input, input2));
	PUINT32toSHORT2(__vavgu2(input, input2));
	PUINT32toSHORT2(__vcmpeq2(input, input2));
	PUINT32toSHORT2(__vcmpges2(input, input2));
	PUINT32toSHORT2(__vcmpgeu2(input, input2));
	PUINT32toSHORT2(__vcmpgts2(input, input2));
#endif
}

__global__ void k_simd_u8x4(void)
{
#if !defined(__HIPCC__)
	unsigned int input = UINT8x4toUINT32(-1, -2, -3, -4);
	unsigned int input2 = UINT8x4toUINT32(1, 2, 3, 4);
	PUINT32toINT8x4(input);
	PUINT32toINT8x4(input2);
	PUINT32toINT8x4(__vabs4(input));
	PUINT32toINT8x4(__vabsdiffs4(input, input2));
	PUINT32toUINT8x4(__vabsdiffu4(input2, input));
	PUINT32toINT8x4(__vabsss4(input));
	PUINT32toUINT8x4(__vadd4(input2, input2));
	PUINT32toUINT8x4(__vaddss4(input2, input2));
	PUINT32toUINT8x4(__vaddus4(input2, input2));
	PUINT32toUINT8x4(__vavgs4(input2, input2));
	PUINT32toUINT8x4(__vavgu4(input2, input2));
	PUINT32toUINT8x4(__vcmpeq4(input2, input2));
	PUINT32toUINT8x4(__vcmpges4(input2, input2));
	PUINT32toUINT8x4(__vcmpgeu4(input2, input2));
	PUINT32toUINT8x4(__vcmpgts2(input2, input2));
#endif
}

int main(int argc, char *argv[])
{
	k_simd_types<<<1, 1>>>();

	k_simd_u16x2<<<1, 1>>>();
	k_simd_u8x4<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
