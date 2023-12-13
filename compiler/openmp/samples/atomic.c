#include <stdio.h>
#include <omp.h>


int main(int argc, char *argv[])
{
	int i, j, id;
	int count = 0;

	omp_set_num_threads(10);

	#pragma omp parallel for
	for (i = 0; i < 25; i++) {
		#pragma omp critical
		count++;
	}
	printf("count = %d\n",count);

	#pragma omp parallel for
	for (i = 0; i < 25; i++) {
		#pragma omp atomic
		count -- ;
	}
	printf("count = %d\n",count);
	return 0;
}
