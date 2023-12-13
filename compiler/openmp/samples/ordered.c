#include <stdio.h>
#include <omp.h>

/*
 * setenv OMP_SCHEDULE "dynamic, 2"; enviroment variable
 */

int main(int argc, char *argv[])
{
	int i, j, id;

	#pragma omp parallel
	{
		#pragma omp for
		for (j = 0; j < 5; j++)
			printf("---: j = %d, id = %d\n",j,omp_get_thread_num());
		#pragma omp for ordered
		for (j = 0; j < 5; j++) {
			printf("+++: j = %d, id = %d\n",j,omp_get_thread_num());
		}
	}
}
