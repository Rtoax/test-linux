#include <omp.h>
#include <stdio.h>

int main(void)
{
	int i = omp_get_thread_limit();
	printf("omp_get_thread_limit = %d\n", i);
	return 0;
}
