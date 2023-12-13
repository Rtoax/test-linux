#include <stdio.h>
#ifdef _OPENMP
#include <omp.h>
#endif


int main(int argc, char *argv[])
{
	int sum = 0;

	#ifdef _OPENMP
	omp_set_num_threads(5);
	omp_set_nested(1);
	#endif

	#ifdef _OPENMP
	#pragma omp parallel num_threads(2)
	#endif
	{
		int a = 0;

		#ifdef _OPENMP
		printf("loop1: id = %d, a = %d\n", omp_get_thread_num(), a);
		#endif

		#ifdef _OPENMP
		#pragma omp barrier
		#endif

		#ifdef _OPENMP
		#pragma omp parallel num_threads(4)
		#endif
		{
			a = 1;
			#ifdef _OPENMP
			printf("loop1: id = %d, a = %d\n", omp_get_thread_num(), a);
			#endif
		}
	}
	printf("sum = %d\n",sum);
	return 0;
}
