#include <stdio.h>
#include <omp.h>


int main(void)
{
	int count = 0, i;

	#pragma omp parallel
	{
		printf("count = %d\n", count++);
		#pragma omp barrier
	}
	return 0;
}
