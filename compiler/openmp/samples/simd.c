#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

void daxpy(double *x, double *y, double a, int n)
{
	int i;
	#pragma omp parallel for simd
	for (i = 0; i < n; i++) {
		y[i] = a * x[i] + y[i];
	}
}

int main(int argc, char *argv[])
{
	double x[] = {1,2,3,4,5,6,4,3,2,1,2,7,9,5,3,2,4,5,7,6,5,2,3,5,7,5};
	double y[] = {1,2,3,4,5,6,4,3,2,1,2,7,9,5,3,2,4,5,7,6,5,2,3,5,7,5};
	double a = 1.1;

	omp_set_num_threads(10);

	daxpy(x, y, a, ARRAY_SIZE(x));

	return 0;
}
