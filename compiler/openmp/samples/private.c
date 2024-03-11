#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
	int j = 99;

	#pragma omp parallel for private(j) num_threads(6)
	for (j = 0; j < 5; j++) {
		printf("j = %d\n", j);
	}

	printf("-------------\n");

	#pragma omp parallel for private(j)
	for (j = 0; j < 5; j++) {
		printf("j = %d\n", j);
	}

	printf("-------------\n");

	printf("j = %d\n", j);
	return 0;
}
