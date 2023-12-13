#include<stdio.h>
#include<omp.h>


int global = 0;
#pragma omp threadprivate(global)

int main(void)
{
	global = 333;
	int i;
	#pragma omp parallel for copyin(global)
	for (i = 0; i < 7; i++) {
		printf("Before: global = %d\n", global);
		global = omp_get_thread_num();
		printf(" After: global = %d\n", global);
	}
	#pragma omp parallel for
	for (i = 0; i < 5; i++) {
		printf("#Again: global = %d\n", global);
	}
	return 0;
}
