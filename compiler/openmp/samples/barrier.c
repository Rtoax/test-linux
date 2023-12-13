#include <stdio.h>
#include <omp.h>

/*
 * setenv OMP_SCHEDULE "dynamic, 2"; enviroment variable
 */

int main(int argc, char *argv[])
{
	int i, j, id;
	int count = 0;

	omp_set_num_threads(10);

	#pragma omp parallel
	{
		printf("before: id = %d/%d\n",omp_get_thread_num(),omp_get_num_threads());
		#pragma omp barrier
		printf(" after: id = %d/%d\n",omp_get_thread_num(),omp_get_num_threads());
	}
	return 0;
}
