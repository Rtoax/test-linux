#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
	int j = 99;
	int sum = 0;

	#pragma omp parallel for
	for (j = 0; j < 5; j++) {
		#pragma omp flush(sum)
		if (!sum)
			sum = 1;
		printf("sum = %d\n",sum);
	}
	return 0;
}
