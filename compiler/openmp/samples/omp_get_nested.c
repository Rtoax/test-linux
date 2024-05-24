#include <omp.h>
#include <stdio.h>

int main(void)
{
	int i = omp_get_nested();
	printf("omp_get_nested = %d\n", i);
	return 0;
}
