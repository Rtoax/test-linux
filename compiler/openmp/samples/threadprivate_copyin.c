#include <stdio.h>
#include <omp.h>


int m = 3;
#pragma omp threadprivate(m)

int main(int argc, char *argv[])
{
	int i = 97, j = 99, id;
	int sum = 0;

	m = 13;
	#pragma omp parallel for copyin(m)
	for (j = 0; j < 5; j++) {
		m += j;
		printf("m = %d\n",m);
	}

	m = 99;

	#pragma omp parallel for
	for (j = 0; j < 5; j++) {
		printf("--m = %d\n",m);
	}
	return 0;
}
