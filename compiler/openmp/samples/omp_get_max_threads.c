#include <omp.h>
#include <stdio.h>

int main(void)
{
	int i = omp_get_max_threads();
	printf("omp_get_max_threads = %d\n", i);
	return 0;
}
