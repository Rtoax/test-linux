#include <stdio.h>
#ifdef _OPENMP
#include <omp.h>
#endif


int main(int argc, char *argv[])
{
	int sum = 0, i;

	#ifdef _OPENMP
	omp_set_num_threads(5);
	omp_set_nested(1);
	#endif

	#ifdef _OPENMP
	#pragma omp parallel num_threads(2)
	#endif
	{
		int a = 0;
		int b = 10;
		int c = 0;

		#ifdef _OPENMP
		printf("loop1: id = %d, a = %d\n", omp_get_thread_num(), a);
		#endif

		#ifdef _OPENMP
		#pragma omp barrier
		#endif

		#ifdef _OPENMP
		#pragma omp parallel num_threads(4) firstprivate(b) reduction(+:c)
		#endif
		{
			a = 1;
			b = b + 10;
			c = b;

			#ifdef _OPENMP
			printf("loop2: id = %d, a = %d, c = %d\n", omp_get_thread_num(), a, c);
			#endif
		}
		printf("loop3: id = %d, a = %d, c = %d\n", omp_get_thread_num(), a, c);
	}
	return 0;
}
