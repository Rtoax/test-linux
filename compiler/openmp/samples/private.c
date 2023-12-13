#include <stdio.h>
#include <omp.h>


int main(int argc, char *argv[])
{
	int i, j = 99, id;
	int sum = 0;

	#pragma omp parallel for private(j) num_threads(6)
	for (j = 0; j < 5; j++) {
		printf("j = %d\n",j);
	}
	printf("j = %d\n",j);
}
