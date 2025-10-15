// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
/**
 * https://docs.nvidia.com/cuda/cuda-math-api/cuda_math_api/group__CUDA__MATH__DOUBLE.html
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


__global__ void k_double_precision_mathematical(void)
{
	double pi = 3.141592653, tmp, tmp2;
	int i;

	PDOUBLE(pi);

	PDOUBLE(acos(pi));
	PDOUBLE(acosh(pi));
	PDOUBLE(asin(pi));
	PDOUBLE(asinh(pi));
	PDOUBLE(atan(pi));
	PDOUBLE(atan2(pi, pi));
	PDOUBLE(atanh(pi));

	PDOUBLE(cbrt(pi));
	PDOUBLE(ceil(pi));
	PDOUBLE(copysign(pi, pi));
	PDOUBLE(cos(pi));
	PDOUBLE(cosh(pi));
	PDOUBLE(cospi(pi));

	/**
	 * Calculate the value of the regular modified cylindrical Bessel
	 * function of order 0 for the input argument.
	 */
	PDOUBLE(cyl_bessel_i0(pi));
	PDOUBLE(cyl_bessel_i1(pi));

	PDOUBLE(erf(pi)); /* error function */
	PDOUBLE(erfc(pi)); /* complementary error function */
	PDOUBLE(erfcinv(pi)); /* inverse complementary error function */
	PDOUBLE(erfcx(pi));
	PDOUBLE(erfinv(pi));

	PDOUBLE(exp(pi));
	PDOUBLE(exp10(pi));
	PDOUBLE(exp2(pi));
	PDOUBLE(expm1(pi));
	PDOUBLE(fabs(pi));

	PDOUBLE(fdim(pi, pi));

	PDOUBLE(floor(pi));

	PDOUBLE(fma(pi, pi, pi));

	PDOUBLE(fmax(pi, 1.));
	PDOUBLE(fmin(pi, 1.));
	PDOUBLE(fmod(pi, 1.));

	PDOUBLE(frexp(pi, &i));
	PINT(i);

	PDOUBLE(hypot(pi, 1.));

	PINT(ilogb(pi));

	PBOOL(isfinite(pi));
	PBOOL(isinf(pi));
	PBOOL(isnan(pi));

	PDOUBLE(j0(pi));
	PDOUBLE(j1(pi));
	PDOUBLE(jn(1, pi));

	PDOUBLE(ldexp(pi, 1));

	PDOUBLE(lgamma(pi));
	PLONG(lrint(pi));
	PLONGLONG(llrint(pi));
	PLONG(lround(pi));
	PLONGLONG(llround(pi));

	PDOUBLE(round(pi));

	PDOUBLE(log(pi));
	PDOUBLE(log10(pi));
	PDOUBLE(log1p(pi));
	PDOUBLE(log2(pi));
	PDOUBLE(logb(pi));

	PDOUBLE(max(1., 2.));
	PDOUBLE(max(1.f, 2.));
	PDOUBLE(max(1., 2.f));
	PDOUBLE(min(1., 2.));
	PDOUBLE(min(1.f, 2.));
	PDOUBLE(min(1., 2.f));

	PDOUBLE(modf(pi, &tmp));

	PDOUBLE(nan(""));

	PDOUBLE(nearbyint(pi));
	PDOUBLE(nextafter(pi, 1.));

	PDOUBLE(norm(1, &pi));
	PDOUBLE(norm3d(pi, pi, pi));
	PDOUBLE(norm4d(pi, pi, pi, pi));
	PDOUBLE(normcdf(pi));
	PDOUBLE(normcdfinv(pi));

	PDOUBLE(rnorm(1, &pi));
	PDOUBLE(rnorm3d(pi, pi, pi));
	PDOUBLE(rnorm4d(pi, pi, pi, pi));

	PDOUBLE(pow(pi, 2.));

	PDOUBLE(rcbrt(pi));
	PDOUBLE(remainder(pi, pi));
	PDOUBLE(remquo(pi, pi, &i));
	PINT(i);

	PDOUBLE(rhypot(pi, pi));
	PDOUBLE(rint(pi));

	PDOUBLE(sqrt(pi));
	PDOUBLE(rsqrt(pi));

	PDOUBLE(scalbln(pi, 2));
	PDOUBLE(scalbn(pi, 2));

	PBOOL(signbit(pi));

	PDOUBLE(sin(pi));
	PEXPR(sincos(pi, &tmp, &tmp2));
	PDOUBLE(tmp);
	PDOUBLE(tmp2);
	PEXPR(sincospi(1., &tmp, &tmp2));
	PDOUBLE(tmp);
	PDOUBLE(tmp2);
	PDOUBLE(sinh(pi));
	PDOUBLE(sinpi(1.));

	PDOUBLE(tan(pi));
	PDOUBLE(tanh(pi));

	PDOUBLE(tgamma(pi));
	PDOUBLE(trunc(pi));

	PDOUBLE(y0(pi));
	PDOUBLE(y1(pi));
	PDOUBLE(yn(2, pi));
}

__global__ void k_double_precision_intrinsics(void)
{
	double pi = 3.141592653;

	PDOUBLE(__dadd_rd(pi, pi));
	PDOUBLE(__dadd_rn(pi, pi));
	PDOUBLE(__dadd_ru(pi, pi));
	PDOUBLE(__dadd_rz(pi, pi));

	PDOUBLE(__dsub_rd(pi, pi));
	PDOUBLE(__dsub_rn(pi, pi));
	PDOUBLE(__dsub_ru(pi, pi));
	PDOUBLE(__dsub_rz(pi, pi));

	PDOUBLE(__ddiv_rd(pi, pi));
	PDOUBLE(__ddiv_rn(pi, pi));
	PDOUBLE(__ddiv_ru(pi, pi));
	PDOUBLE(__ddiv_rz(pi, pi));

	PDOUBLE(__dmul_rd(pi, pi));
	PDOUBLE(__dmul_rn(pi, pi));
	PDOUBLE(__dmul_ru(pi, pi));
	PDOUBLE(__dmul_rz(pi, pi));

	PDOUBLE(__drcp_rd(pi));
	PDOUBLE(__drcp_rn(pi));
	PDOUBLE(__drcp_ru(pi));
	PDOUBLE(__drcp_rz(pi));

	PDOUBLE(__dsqrt_rd(pi));
	PDOUBLE(__dsqrt_rn(pi));
	PDOUBLE(__dsqrt_ru(pi));
	PDOUBLE(__dsqrt_rz(pi));

	PDOUBLE(__fma_rd(pi, pi, pi));
	PDOUBLE(__fma_rn(pi, pi, pi));
	PDOUBLE(__fma_ru(pi, pi, pi));
	PDOUBLE(__fma_rz(pi, pi, pi));
}

int main(int argc, char *argv[])
{
	assert(sizeof(double) == 8 && "bad size of double");

	k_double_precision_mathematical<<<1, 1>>>();
	k_double_precision_intrinsics<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
