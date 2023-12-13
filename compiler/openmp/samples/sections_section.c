#include <stdio.h>
#include <omp.h>

/*
 *setenv OMP_SCHEDULE "dynamic, 2"; enviroment variable
 */

int main(int argc, char *argv[])
{
	omp_set_num_threads(10);
	#pragma omp parallel
	{
		#pragma omp sections
		{
			#pragma omp section
			printf("section11, id = %2d\n",omp_get_thread_num());

			#pragma omp section
			printf("section12, id = %2d\n",omp_get_thread_num());

			#pragma omp section
			printf("section13, id = %2d\n",omp_get_thread_num());

			#pragma omp section
			printf("section14, id = %2d\n",omp_get_thread_num());
		}
		#pragma omp sections
		{
			#pragma omp section
			printf("section21, id = %2d\n",omp_get_thread_num());

			#pragma omp section
			printf("section22, id = %2d\n",omp_get_thread_num());

			#pragma omp section
			printf("section23, id = %2d\n",omp_get_thread_num());

			#pragma omp section
			printf("section24, id = %2d\n",omp_get_thread_num());
		}
	}
	return 0;
}
