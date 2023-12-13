#include <stdio.h>
#include <omp.h>

/*
 * setenv OMP_SCHEDULE "dynamic, 2"; enviroment variable
 */

int main(int argc, char *argv[])
{
	int i, j, id;

	omp_set_num_threads(10);
	#pragma omp parallel
	{
		#pragma omp single
		printf("section11, id = %2d\n",omp_get_thread_num());

		printf("section12, id = %2d\n",omp_get_thread_num());

		#pragma omp single
		printf("section13, id = %2d\n",omp_get_thread_num());

		#pragma omp single
		printf("section14, id = %2d\n",omp_get_thread_num());
	}
}
