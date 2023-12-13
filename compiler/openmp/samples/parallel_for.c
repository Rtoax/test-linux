#include <stdio.h>
#ifdef _OPENMP
#include <omp.h>
#endif


int main(int argc, char *argv[]){

#ifdef _OPENMP
	omp_set_num_threads(10);
	#pragma omp parallel num_threads(3)
#endif
	{

		printf("hello world\n");
	}
	int j;
#ifdef _OPENMP
	omp_set_num_threads(5);
	#pragma omp parallel
	{
		#pragma omp for
		for (j = 0; j < 7; j++){
			printf("1: j = %d, ThreadId = %d\n", j, omp_get_thread_num());
		}
		#pragma omp for
		for (j = 0; j < 7; j++){
			printf("2: j = %d, ThreadId = %d\n", j, omp_get_thread_num());
		}
	}
#endif
}
