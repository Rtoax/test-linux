#include <stdio.h>
#include <omp.h>

/*
 * setenv OMP_SCHEDULE "dynamic, 2"; enviroment variable
 */

int main(int argc, char *argv[])
{
	int j;
	int a[5];

	omp_set_num_threads(4);

	#pragma omp parallel
	{
		#pragma omp for
		for (j = 0; j < 5; j++)
			a[j] = j * j;
		#pragma omp masked
		for (j = 0; j < 5; j++)
			printf(" a[%d] = %d, j = %d, id = %d/%d\n",
				j, a[j],j,omp_get_thread_num(),omp_get_num_threads());
	}
	return 0;
}

