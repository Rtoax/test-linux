// SPDX-License-Identifier: GPL-3.0
/* Copyright (C) 2026 Rong Tao */
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <cuda_runtime.h>
#include <cuComplex.h>
#include "compiler.h"
#include "print.h"
#include "types.h"

__global__ void k_cuFloatComplex(void)
{
	cuFloatComplex f_pi = make_cuFloatComplex(PI_FLOAT, PI_FLOAT);
	cuComplex pi = make_cuComplex(PI_FLOAT, PI_FLOAT);

	PCOMPLEX(f_pi);
	PCOMPLEX(pi);

	PFLOAT(cuCrealf(f_pi));
	PFLOAT(cuCimagf(f_pi));

	PCOMPLEX(cuConjf(f_pi));
	PCOMPLEX(cuCaddf(f_pi, f_pi));
	PCOMPLEX(cuCsubf(f_pi, f_pi));
	PCOMPLEX(cuCmulf(f_pi, f_pi));
	PCOMPLEX(cuCdivf(f_pi, f_pi));
	PFLOAT(cuCabsf(f_pi));

	PCOMPLEX(cuCfmaf(f_pi, f_pi, f_pi));

	PCOMPLEXD(cuComplexFloatToDouble(f_pi));
}

__global__ void k_cuDoubleComplex(void)
{
	cuDoubleComplex d_pi = make_cuDoubleComplex(PI_DOUBLE, PI_DOUBLE);

	PCOMPLEXD(d_pi);

	PDOUBLE(cuCreal(d_pi));
	PDOUBLE(cuCimag(d_pi));

	PCOMPLEXD(cuConj(d_pi));
	PCOMPLEXD(cuCadd(d_pi, d_pi));
	PCOMPLEXD(cuCsub(d_pi, d_pi));
	PCOMPLEXD(cuCmul(d_pi, d_pi));
	PCOMPLEXD(cuCdiv(d_pi, d_pi));
	PDOUBLE(cuCabs(d_pi));

	PCOMPLEXD(cuCfma(d_pi, d_pi, d_pi));

	PCOMPLEX(cuComplexDoubleToFloat(d_pi));
}

int main(int argc, char *argv[])
{
	assert(sizeof(cuComplex) == 8 && "bad size of cuComplex");
	assert(sizeof(cuFloatComplex) == 8 && "bad size of cuFloatComplex");
	assert(sizeof(cuDoubleComplex) == 16 && "bad size of cuDoubleComplex");

	k_cuFloatComplex<<<1, 1>>>();
	k_cuDoubleComplex<<<1, 1>>>();

	(void)cudaDeviceSynchronize();
	return 0;
}
