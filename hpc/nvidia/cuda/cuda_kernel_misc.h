// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2026 Rong Tao */
#ifndef __CUDA_KERNEL_MISC_H
#define __CUDA_KERNEL_MISC_H 1

__device__ __forceinline__ unsigned int __laneid(void)
{
	unsigned int laneid;
#if defined(__HPCC__) || defined(__LUCA__) || defined(__HIPCC__)
	laneid = __lane_id();
#else
	asm("mov.u32 %0, %%laneid;" : "=r"(laneid));
#endif
	return laneid;
}

#endif
