/**
 * _OPENMP (sync Doc::openmp.rst)
 *
 * - 200505：OpenMP 2.5
 * - 200805：OpenMP 3.0
 * - 201107：OpenMP 3.1
 * - 201307：OpenMP 4.0
 * - 201511：OpenMP 4.5
 * - 201811：OpenMP 5.0
 * - 202011：OpenMP 5.1
 * - 202111：OpenMP 5.2
 * - 202411: OpenMP 6.0
 */
#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
#ifdef __STDC_VERSION__
	printf("__STDC_VERSION__ = %ld, ", __STDC_VERSION__);
#endif
#ifdef __OPENMP__
	printf("__OPENMP__ = %d, ", __OPENMP__);
#endif
	printf("_OPENMP = %d\n", _OPENMP);
	return 0;
}
