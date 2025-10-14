// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * https://docs.nvidia.com/cuda/cuda-math-api/cuda_math_api/group__CUDA__MATH__SINGLE.html
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


__global__ void k_float_precision_mathematical(void)
{
	float pi = 3.141592653f;
	float tmp, tmp2, tmp3;
	int i = 1;

	PFLOAT(acosf(pi));
	PFLOAT(acoshf(pi));
	PFLOAT(asinf(pi));
	PFLOAT(asinhf(pi));
	PFLOAT(atanf(pi));
	PFLOAT(atan2f(pi, pi));
	PFLOAT(cbrtf(pi)); /* cube root */
	PFLOAT(ceilf(pi));
	PFLOAT(floorf(pi));
#if !defined(__HPCC__)
	PFLOAT(copysignf(pi, pi));
#endif
	PFLOAT(cosf(pi));
	PFLOAT(coshf(pi));
	PFLOAT(cospif(pi)); /* cosine of the input argument *pi */
	/**
	 * Calculate the value of the regular modified cylindrical Bessel
	 * function of order 0 for the input argument.
	 */
	PFLOAT(cyl_bessel_i0f(pi));
	PFLOAT(cyl_bessel_i1f(pi));
	PFLOAT(erfcf(pi));
	PFLOAT(erfcinvf(pi));
	PFLOAT(erfcxf(pi));
	PFLOAT(erff(pi));
	PFLOAT(erfinvf(pi));
	PFLOAT(exp10f(pi));
	PFLOAT(exp2f(pi));
	PFLOAT(expf(pi));
	PFLOAT(expm1f(pi));
	PFLOAT(fabsf(pi));
	PFLOAT(fdimf(pi, 1.0f));
	PFLOAT(fdividef(pi, pi));
	PFLOAT(fmaf(pi, pi, pi));
	PFLOAT(fmaxf(pi, pi));
	PFLOAT(fminf(pi, pi));
	PFLOAT(fmodf(pi, pi));
	PFLOAT(frexpf(pi, &i));
	PINT(i);
	PFLOAT(hypotf(pi, pi));
	PINT(ilogbf(pi));
	PBOOL(isfinite(pi));
	PBOOL(isinf(pi));
	PBOOL(isnan(pi));
	/**
	 * Calculate the value of the Bessel function of the first kind of
	 * order 0 for the input argument.
	 */
	PFLOAT(j0f(pi));
	PFLOAT(j1f(pi));
	PFLOAT(jnf(2, pi));
	PFLOAT(ldexpf(pi, 2));
	PFLOAT(lgammaf(pi));
	PLONGLONG(llrintf(pi));
	PLONGLONG(llroundf(pi));
	PFLOAT(log10f(pi));
	PFLOAT(log1pf(pi));
	PFLOAT(log2f(pi));
	PFLOAT(logbf(pi));
	PFLOAT(logf(pi));
	PLONG(lrintf(pi));
	PLONG(lroundf(pi));
	PFLOAT(max(pi, 1.f));
	PFLOAT(min(pi, 1.f));
	PFLOAT(modff(pi, &tmp));
	PFLOAT(tmp);
	PFLOAT(nanf(""));
	PFLOAT(nearbyintf(pi));
	PFLOAT(nextafterf(pi, 1.f));
	PFLOAT(norm3df(1.f, 2.f, 3.f));
	PFLOAT(norm4df(1.f, 2.f, 3.f, 4.f));
	PFLOAT(normcdff(pi));
	PFLOAT(normcdfinvf(pi));
	PFLOAT(normf(1, &pi));
	PFLOAT(powf(pi, 2.f));
	PFLOAT(rcbrtf(pi));
	PFLOAT(remainderf(pi, 2.f));
	PFLOAT(remquof(pi, 2.f, &i));
	PFLOAT(rhypotf(pi, 2.f));
	PFLOAT(rintf(pi));
	PFLOAT(rnorm3df(1.f, 2.f, 3.f));
	PFLOAT(rnorm4df(1.f, 2.f, 3.f, 4.f));
	PFLOAT(rnormf(1, &pi));
	PFLOAT(roundf(pi));
	PFLOAT(rsqrtf(pi));
	PFLOAT(scalblnf(pi, 2));
	PFLOAT(scalbnf(pi, 2));
	PINT(signbit(pi));
	PINT(signbit(-pi));
	PEXPR(sincosf(pi, &tmp2, &tmp3));
	PFLOAT(tmp2);
	PFLOAT(tmp3);
	PFLOAT(sinf(pi));
	PFLOAT(sinhf(pi));
	PFLOAT(sinpif(pi));
	PFLOAT(sqrtf(pi));
	PFLOAT(tanf(pi));
	PFLOAT(tanhf(pi));
	PFLOAT(tgammaf(pi));
	PFLOAT(truncf(pi));
	PFLOAT(y0f(pi));
	PFLOAT(y1f(pi));
	PFLOAT(ynf(1, pi));
}

int main(int argc, char *argv[])
{
	assert(sizeof(float) == 4 && "bad size of float");
	assert(sizeof(float2) == 8 && "bad size of float2");

	k_float_precision_mathematical<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
