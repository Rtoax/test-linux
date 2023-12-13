#include <stdio.h>
#include <omp.h>


int main(int argc, char *argv[])
{
	int i, j, id;
	omp_set_num_threads(10);
	#pragma omp parallel num_threads(3)
	{
		#pragma omp for schedule(dynamic)
		for (i = 0; i < 13; i++) {
			printf("no size: i = %2d, id = %2d\n",i,omp_get_thread_num());
		}
		#pragma omp for schedule(dynamic,2)
		for (i = 0; i < 13; i++) {
			printf("   size: i = %2d, id = %2d\n",i,omp_get_thread_num());
		}
	}
	return 0;
}
