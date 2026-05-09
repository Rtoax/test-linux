#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void)
{
	int i, sum = 0;
	#pragma omp parallel for reduction(+:sum)
	for (i = 0; i < 5 ; i++) {
		sum += i;
		printf("i = %d, sum = %d\n",i,sum);
	}
	printf("sum = %d\n",sum);
	printf("##################################################\n");

	#pragma omp parallel for schedule(dynamic, 3)
	for (i = 0; i < 12; i++) {
		printf("i = %d\n",i);
	}

	printf("##################################################\n");

	#pragma omp parallel sections
	{
		#pragma omp section
		printf("section:1, id = %d/%d\n", omp_get_thread_num(),omp_get_num_threads());
	}
	printf("##################################################\n");

	#pragma omp parallel
	{
		#pragma omp single
		printf("1\n");
		/**
		 * error: ‘master’ construct deprecated since OpenMP 5.1, use ‘masked’
		 */
		#if _OPENMP < 202011
		#pragma omp master
		#else
		#pragma omp masked
		#endif
		printf("2\n");
		#pragma omp single nowait
		printf("3\n");
		#pragma omp single nowait
		printf("4\n");
	}
	printf("##################################################\n");
	i = 0;

	#pragma omp parallel
	{
		#pragma omp for nowait
		for (i = 0;i < 5; i++) {
			printf("-%d-",i);
		}
		printf("-%d-\n", i);
	}
	return 0;
}
