#include <stdio.h>
#include <omp.h>

/*
 * setenv OMP_SCHEDULE "dynamic, 2"; enviroment variable
 */

int main(int argc, char *argv[])
{
	int i;

	omp_set_num_threads(10);
	#pragma omp parallel num_threads(2)
	{
		#pragma omp for schedule(runtime)
		for (i = 0; i < 5; i++) {
			printf("no size: i = %2d, id = %2d\n",i,omp_get_thread_num());
		}
		#pragma omp single
		printf("\n");
	}
	return 0;
}
