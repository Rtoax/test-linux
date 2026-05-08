#include <omp.h>
#include <stdio.h>

int main(void)
{
	/**
	 * Since OpenMP 5.0, omp_get_nested() is deprecated
	 */
	int i = omp_get_nested();
	printf("omp_get_nested = %d\n", i);
	return 0;
}
