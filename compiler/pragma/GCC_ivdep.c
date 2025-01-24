/**
 * #pragma GCC ivdep
 *
 * With this pragma, the programmer asserts that there are no loop-carried
 * dependencies which would prevent consecutive iterations of the following
 * loop from executing concurrently with SIMD (single instruction multiple
 * data) instructions.
 *
 * refs:
 * - https://gcc.gnu.org/onlinedocs/gcc/Loop-Specific-Pragmas.html
 */

/**
 * For example, the compiler can only unconditionally vectorize the following
 * loop with the pragma:
 *
 * In this example, using the restrict qualifier had the same effect.
 */
void foo(int n, int *a, int *b, int *c)
{
	int i;
#if defined(__clang__)
#elif defined(__GNUC__)
	#pragma GCC ivdep
#endif
	for (i = 0; i < n; ++i)
		a[i] = b[i] + c[i];
}

/**
 *
 */
void ignore_vec_dep(int *a, int k, int c, int m)
{
#if defined(__clang__)
#elif defined(__GNUC__)
	#pragma GCC ivdep
#endif
	for (int i = 0; i < m; i++)
		a[i] = a[i + k] * c;
}

int main(void)
{
	return 0;
}
