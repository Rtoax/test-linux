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
	unsigned int input3 = UINT16x2toUINT32(3, 4);
	bool pred_hi, pred_lo;

	PUINT32toINT16x2(input);
	PUINT32toINT16x2(input2);
	PUINT32toINT16x2(input3);

	PUINT32toINT16x2(__vneg2(input));
	PUINT32toINT16x2(__vnegss2(input)); /* signed saturation */

	PINT32(__vseteq2(input, input));
	PINT32(__vsetges2(input, input));
	PINT32(__vsetgeu2(input, input));
	PINT32(__vsetgts2(input, input));
	PINT32(__vsetgtu2(input, input));
	PINT32(__vsetles2(input, input));
	PINT32(__vsetleu2(input, input));
	PINT32(__vsetlts2(input, input));
	PINT32(__vsetltu2(input, input));
	PINT32(__vsetne2(input, input));

	PUINT32toSHORT2(__vabs2(input));
	PUINT32toSHORT2(__vabsdiffs2(input, input2));
	PUINT32toSHORT2(__vabsdiffu2(input, input2));
	PUINT32toSHORT2(__vabsss2(input));

	PUINT32toSHORT2(__vsub2(input, input2));
	PUINT32toSHORT2(__vsubss2(input, input2));
	PUINT32toSHORT2(__vsubus2(input, input2));

	PUINT32toSHORT2(__vadd2(input, input2));
	PUINT32toSHORT2(__vaddss2(input, input2));
	PUINT32toSHORT2(__vaddus2(input, input2));
	PUINT32toSHORT2(__vhaddu2(input, input2));
	PUINT32toSHORT2(__vsads2(input, input2));
	PUINT32toSHORT2(__vsadu2(input, input2));

	PUINT32toSHORT2(__vavgs2(input, input2));
	PUINT32toSHORT2(__vavgu2(input, input2));

	PUINT32toSHORT2(__vcmpeq2(input, input2));
	PUINT32toSHORT2(__vcmpges2(input, input2));
	PUINT32toSHORT2(__vcmpgeu2(input, input2));
	PUINT32toSHORT2(__vcmpgts2(input, input2));
	PUINT32toSHORT2(__vcmpgtu2(input, input2));
	PUINT32toSHORT2(__vcmples2(input, input2));
	PUINT32toSHORT2(__vcmpleu2(input, input2));
	PUINT32toSHORT2(__vcmplts2(input, input2));
	PUINT32toSHORT2(__vcmpltu2(input, input2));
	PUINT32toSHORT2(__vcmpne2(input, input2));

	PUINT32toSHORT2(__vmaxs2(input, input2));
	PUINT32toSHORT2(__vmaxu2(input, input2));
	PUINT32toSHORT2(__vmins2(input, input2));
	PUINT32toSHORT2(__vminu2(input, input2));

	PUINT32toSHORT2(__viaddmax_s16x2(input, input2, input3)); /* max(a + b, c) */
	PUINT32toSHORT2(__viaddmax_s16x2_relu(input, input2, input3)); /* max(max(a + b, c), 0) */
	PUINT32toSHORT2(__viaddmin_s16x2_relu(input, input2, input3)); /* max(min(a + b, c), 0) */
	PUINT32toSHORT2(__viaddmax_u16x2(input, input2, input3)); /* max(a + b, c) */
	PUINT32toSHORT2(__viaddmin_u16x2(input, input2, input3)); /* min(a + b, c) */
	/**
	 * Performs per-halfword max(a, b), also sets the value pointed to by
	 * pred_hi and pred_lo to the per-halfword result of (a >= b).
	 */
	PUINT32toSHORT2(__vibmax_s16x2(input, input2, &pred_hi, &pred_lo));
		PBOOL(pred_hi);
		PBOOL(pred_lo);
	PUINT32toSHORT2(__vibmax_u16x2(input, input2, &pred_hi, &pred_lo));
		PBOOL(pred_hi);
		PBOOL(pred_lo);
	/**
	 * Performs per-halfword min(a, b), also sets the value pointed to by
	 * pred_hi and pred_lo to the per-halfword result of (a <= b).
	 */
	PUINT32toSHORT2(__vibmin_u16x2(input, input2, &pred_hi, &pred_lo));
		PBOOL(pred_hi);
		PBOOL(pred_lo);

	PUINT32toSHORT2(__vimax3_s16x2(input, input2, input3)); /* max(max(a, b), c) */
	PUINT32toSHORT2(__vimax3_s16x2_relu(input, input2, input3)); /* max(max(max(a, b), c), 0) */
	PUINT32toSHORT2(__vimax3_u16x2(input, input2, input3)); /* max(max(a, b), c) */

	PUINT32toSHORT2(__vimin3_s16x2(input, input2, input3)); /* min(min(a, b), c) */
	PUINT32toSHORT2(__vimin3_s16x2_relu(input, input2, input3)); /* max(min(min(a, b), c), 0) */
	PUINT32toSHORT2(__vimin3_u16x2(input, input2, input3)); /* min(min(a, b), c) */

	PUINT32toSHORT2(__vimax_s16x2_relu(input, input2)); /* max(max(a, b), 0) */
	PUINT32toSHORT2(__vimin_s16x2_relu(input, input2)); /* max(min(a, b), 0) */
#endif
}

__global__ void k_simd_u8x4(void)
{
#if !defined(__HIPCC__)
	unsigned int input = UINT8x4toUINT32(-1, -2, -3, -4);
	unsigned int input2 = UINT8x4toUINT32(1, 2, 3, 4);

	PUINT32toINT8x4(input);
	PUINT32toINT8x4(input2);

	PUINT32toINT8x4(__vneg4(input));
	PUINT32toINT8x4(__vnegss4(input)); /* signed saturation */

	PINT32(__vseteq4(input, input));
	PINT32(__vsetges4(input, input));
	PINT32(__vsetgeu4(input, input));
	PINT32(__vsetgts4(input, input));
	PINT32(__vsetgtu4(input, input));
	PINT32(__vsetles4(input, input));
	PINT32(__vsetleu4(input, input));
	PINT32(__vsetlts4(input, input));
	PINT32(__vsetltu4(input, input));
	PINT32(__vsetne4(input, input));

	PUINT32toINT8x4(__vabs4(input));
	PUINT32toINT8x4(__vabsdiffs4(input, input2));
	PUINT32toUINT8x4(__vabsdiffu4(input2, input));
	PUINT32toINT8x4(__vabsss4(input));

	PUINT32toUINT8x4(__vadd4(input2, input2));
	PUINT32toUINT8x4(__vaddss4(input2, input2));
	PUINT32toUINT8x4(__vaddus4(input2, input2));
	PUINT32toUINT8x4(__vsads4(input2, input2));
	PUINT32toUINT8x4(__vsadu4(input2, input2));

	PUINT32toUINT8x4(__vsub4(input2, input2));
	PUINT32toUINT8x4(__vsubss4(input2, input2));
	PUINT32toUINT8x4(__vsubus4(input2, input2));

	PUINT32toUINT8x4(__vavgs4(input2, input2));
	PUINT32toUINT8x4(__vavgu4(input2, input2));

	PUINT32toUINT8x4(__vcmpeq4(input2, input2));
	PUINT32toUINT8x4(__vcmpges4(input2, input2));
	PUINT32toUINT8x4(__vcmpgeu4(input2, input2));
	PUINT32toUINT8x4(__vcmpgts4(input2, input2));
	PUINT32toUINT8x4(__vcmpgtu4(input2, input2));
	PUINT32toUINT8x4(__vcmples4(input2, input2));
	PUINT32toUINT8x4(__vcmpleu4(input2, input2));
	PUINT32toUINT8x4(__vcmplts4(input2, input2));
	PUINT32toUINT8x4(__vcmpltu4(input2, input2));
	PUINT32toUINT8x4(__vcmpne4(input2, input2));

	PUINT32toUINT8x4(__vhaddu4(input2, input2));

	PUINT32toUINT8x4(__vmaxs4(input2, input2));
	PUINT32toUINT8x4(__vmaxu4(input2, input2));
	PUINT32toUINT8x4(__vmins4(input2, input2));
	PUINT32toUINT8x4(__vminu4(input2, input2));
#endif
}

__global__ void k_simd_i32(void)
{
	bool pred;

	PINT32(__viaddmax_s32(1, 2, 3)); /* max(a + b, c) */
	PINT32(__viaddmax_s32_relu(1, 2, 3)); /* max(max(a + b, c), 0) */
	PINT32(__viaddmin_s32(1, 2, 3)); /* min(a + b, c) */
	PINT32(__viaddmin_s32_relu(1, 2, 3)); /* max(min(a + b, c), 0) */
	PUINT32(__viaddmax_u32(1, 2, 3)); /* max(a + b, c) */
	PUINT32(__viaddmin_u32(1, 2, 3)); /* min(a + b, c) */
	/* Computes max(a, b), also sets the value pointed to by pred to (a >= b). */
	PINT32(__vibmax_s32(1, 2, &pred));
		PBOOL(pred);
	PINT32(__vibmax_u32(1, 2, &pred));
		PBOOL(pred);
	/* Computes min(a, b), also sets the value pointed to by pred to (a <= b). */
	PINT32(__vibmin_s32(1, 2, &pred));
		PBOOL(pred);
	PINT32(__vibmin_u32(1, 2, &pred));
		PBOOL(pred);

	PUINT32(__vimax3_s32(1, 2, 3)); /* max(max(a, b), c) */
	PUINT32(__vimax3_s32_relu(1, 2, 3)); /* max(max(max(a, b), c), 0) */
	PUINT32(__vimin3_s32(1, 2, 3)); /* min(min(a, b), c) */
	PUINT32(__vimin3_s32_relu(1, 2, 3)); /* max(min(min(a, b), c), 0) */
	PUINT32(__vimax3_u32(1, 2, 3)); /* max(max(a, b), c) */
	PUINT32(__vimin3_u32(1, 2, 3)); /* min(min(a, b), c) */

	PUINT32(__vimax_s32_relu(1, 2)); /* max(max(a, b), 0) */
	PUINT32(__vimin_s32_relu(1, 2)); /* max(min(a, b), 0) */
}

int main(int argc, char *argv[])
{
	k_simd_types<<<1, 1>>>();

	k_simd_u16x2<<<1, 1>>>();
	k_simd_u8x4<<<1, 1>>>();
	k_simd_i32<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
