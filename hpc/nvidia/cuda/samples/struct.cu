// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime.h>

int main(void)
{
#define S(s) printf("Size of '%s' is %ld\n", #s, sizeof(s))

	/* CUfunc_st defined in llvm */
	S(struct CUfunc_st *);

#undef S
	return 0;
}
