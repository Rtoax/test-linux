#include <stdio.h>
#include <omp.h>

double sum(double *A, size_t N)
{
	double sum = 0.0;
	#pragma omp target data map(to: A[0:N])
	{
		#pragma omp target teams distribute parallel for reduction(+:sum)
		for (int i = 0; i < N; ++i) sum += A[i];
	}
	return sum;
}

int main(int argc, char *argv[])
{
	double A[] = { 1, 2, 3 };
	printf("%lf\n", sum(A, 3));
	return 0;
}
