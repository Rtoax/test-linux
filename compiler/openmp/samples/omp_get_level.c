#include <omp.h>
#include <stdio.h>

int main(void)
{
	int i = omp_get_level();
	printf("omp_get_level = %d\n", i);
	return 0;
}
