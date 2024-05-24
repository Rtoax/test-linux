#include <omp.h>
#include <stdio.h>

int main(void)
{
	double d = omp_get_wtick();
	printf("omp_get_wtick = %lf\n", d);
	return 0;
}
