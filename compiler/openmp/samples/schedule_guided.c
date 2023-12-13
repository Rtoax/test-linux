#include <stdio.h>
#include <omp.h>


int main(int argc, char *argv[])
{
	int i;

	omp_set_num_threads(10);
	#pragma omp parallel num_threads(2)
	{
		#pragma omp for schedule(guided)
		for (i = 0; i < 5; i++) {
			printf("no size: i = %2d, id = %2d\n",i,omp_get_thread_num());
		}
		#pragma omp single
		printf("\n");
		#pragma omp for schedule(guided,2)
		for (i = 0; i < 5; i++) {
			printf("   size: i = %2d, id = %2d\n",i,omp_get_thread_num());
		}
	}
	return 0;
}
