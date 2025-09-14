/**
 * Linaro Connect <SVE and SVE2 in LLVM>
 */

/* Example 1: NEON vectorization */
void foo_1(double *a, double *b, double *c, int n)
{
	int i;
	for (i = 0; i < n; i++)
		a[i] = b[i] * c[i];
}

/* Example 2: Simplify the output */
void foo_2(double * __restrict a, double * __restrict b, double * __restrict c, int n)
{
	int i;
#pragma clang loop interleave(disable)
#pragma clang loop unroll(disable)
	for (i = 0; i < n; i++)
		a[i] = b[i] * c[i];
}

/* Example 3: Enable SVE */
void foo_3(double * __restrict a, double * __restrict b, double * __restrict c, int n)
{
	int i;
#pragma clang loop interleave(disable)
#pragma clang loop unroll(disable)
#pragma clang loop vectorize_width(2, scalable)
	for (i = 0; i < n; i++)
		a[i] = b[i] * c[i];
}

/* Example 4: Non-contiguous data */
void foo_4(double * __restrict a, double * __restrict b, double * __restrict c, int *indices, int n)
{
	int i;
#pragma clang loop interleave(disable)
#pragma clang loop unroll(disable)
#pragma clang loop vectorize_width(2, scalable)
	for (i = 0; i < n; i++)
		a[i] = b[i] * c[indices[i]];
}

/* Example 5: Use constants */
void foo_5(double * __restrict a, double * __restrict b, double * __restrict c, int n)
{
	int i;
#pragma clang loop interleave(disable)
#pragma clang loop unroll(disable)
#pragma clang loop vectorize_width(2, scalable)
	for (i = 0; i < n; i++)
		a[i] = b[i] * 4;
}

/* Example 6: Invariant loads */
void foo_6(double * __restrict a, double * __restrict b, double * __restrict c, int n)
{
	int i;
#pragma clang loop interleave(disable)
#pragma clang loop unroll(disable)
#pragma clang loop vectorize_width(2, scalable)
	for (i = 0; i < n; i++)
		a[i] = b[i] * c[0];
}

/* Example 7: Conditional execution */
void foo_7(double * __restrict a, double * __restrict b, double * __restrict c, int n)
{
	int i;
#pragma clang loop interleave(disable)
#pragma clang loop unroll(disable)
#pragma clang loop vectorize_width(2, scalable)
	for (i = 0; i < n; i++)
		if (b[i] > 0)
			a[i] = b[i] * c[i];
}

/* Example 8: Reductions */
double foo_8(double * __restrict a, double * __restrict b, double * __restrict c, int n)
{
	int i;
	double res = 0.0;
#pragma clang loop interleave(disable)
#pragma clang loop unroll(disable)
#pragma clang loop vectorize_width(2, scalable)
	for (i = 0; i < n; i++)
		res += b[i] * c[i];
	return res;
}

/* Example 9: Use induction variable */
double foo_9(double * __restrict a, double * __restrict b, double * __restrict c, int n)
{
	int i;
	double res = 0.0;
#pragma clang loop interleave(disable)
#pragma clang loop unroll(disable)
#pragma clang loop vectorize_width(2, scalable)
	for (i = 0; i < n; i++)
		res += b[i] * i;
	return res;
}

