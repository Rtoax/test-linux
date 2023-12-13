#include <stdio.h>
#include <omp.h>


int main(void)
{
	int i, count = 0;
	#pragma omp parallel
	{
		for (i = 0; i < 15; i++) {
			#pragma omp atomic
			count++;
			printf("i = %d, count = %d\n",i,count);
		}
	}
	printf("count = %d\n",count);
	return 0;
}
