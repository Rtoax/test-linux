#include <stdio.h>
#include <omp.h>

/*
 * setenv OMP_SCHEDULE "dynamic, 2"; enviroment variable
 */

int main(int argc, char *argv[])
{
	int i;
	int max = 0, a[] = {1,2,3,4,5,6,4,3,2,1,2,7,9,5,3,2,4,5,7,6,5,2,3,5,7,5};

	omp_set_num_threads(10);

	#pragma omp parallel for
	for (i = 0; i < 25; i++) {

		#pragma omp critical
		if (max < a[i])
			max = a[i];

		#pragma omp critical
		if (max > a[i])
			a[i] = max;
	}
	printf("max = %d\n",max);

	#pragma omp parallel for
	for (i = 0; i < 25; i++) {
		#pragma omp critical
		printf("a[%d] = %d\n",i,a[i]);
	}
	return 0;
}
