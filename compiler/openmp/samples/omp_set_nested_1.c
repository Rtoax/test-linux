#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
	int sum = 0;

	omp_set_num_threads(5);
	/**
	 * Since OpenMP 5.0, omp_set_nested() is deprecated
	 */
#if _OPENMP < 201811
	omp_set_nested(1);
#else
	omp_set_max_active_levels(1);
#endif

	#pragma omp parallel num_threads(2)
	{
		int a = 0;

		printf("loop1: id = %d, a = %d\n", omp_get_thread_num(), a);

		#pragma omp barrier

		#pragma omp parallel num_threads(4)
		{
			a = 1;
			printf("loop1: id = %d, a = %d\n", omp_get_thread_num(),
			       a);
		}
	}
	printf("sum = %d\n",sum);
	return 0;
}
