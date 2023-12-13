#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
	int i = 97, j = 99, id;
	int sum = 0;

	#pragma omp parallel for lastprivate(i) num_threads(6)
	for (j = 0; j < 5; j++) {
		printf("b: i = %d, j = %d\n",i,j);
		i = j;
		printf("a: i = %d, j = %d\n",i,j);
	}
	printf("i = %d, j = %d\n",i,j);
}
