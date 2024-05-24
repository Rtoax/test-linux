#include <omp.h>
#include <stdio.h>

int main(void)
{
	int i = omp_get_num_procs();
	printf("omp_get_num_procs = %d\n", i);
	return 0;
}
