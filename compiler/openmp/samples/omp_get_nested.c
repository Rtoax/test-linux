#include <omp.h>
#include <stdio.h>

int main(void)
{
	/**
	 * Since OpenMP 5.0, omp_get_nested() is deprecated
	 */
#if _OPENMP < 201811
	int i = omp_get_nested();
	printf("omp_get_nested = %d\n", i);
#else
	int i = omp_get_max_active_levels();
	printf("omp_get_max_active_levels = %d\n", i);
#endif
	return 0;
}
