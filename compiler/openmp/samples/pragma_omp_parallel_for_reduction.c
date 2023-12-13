#include <stdio.h>
#include <omp.h>


static long num_steps = 10000;
double step, pi;

int main(void)
{
	int x=1,y=1,z=0;
	int i, j;
	#pragma omp parallel for private(x,y)
	for (i = 0; i < 3; i++) {
		x = i;
		y = i;
		z = x + y;
		printf("Iter:%d, %d\n",i,z);
	}

	printf("#########################################################\n");

	int sum = 0;
	#pragma omp parallel for
	for (i = 0; i < 5; i++) {
		#pragma omp critical
		sum += i;
		printf("Iter:%d, %d\n",i,sum);
	}
	printf("sum = %d\n",sum);
	printf("#########################################################\n");

	#pragma omp parallel for reduction(+:sum)
	for (i = 0; i < 13; i++) {
		sum += i;
		printf("Iter:%d, %d\n",i,sum);
	}
	printf("sum = %d\n",sum);
	printf("#########################################################\n");


	double xx, ss = 0.0;

	step = 1.0 / (double) num_steps;

	#pragma omp parallel for reduction(+:ss)
	for (i = 0; i < num_steps; i++) {
		xx = (i+0.5)*step;
		ss += 4.0/(1.0 + xx*xx);
	}
	pi = step * ss;
	printf("pi = %lf\n",pi);
	printf("#########################################################\n");

	i = 0;
	int A, B, a = 0, b = 0;
	#pragma omp parallel for reduction(+:a,b)
	for (i = 0; i < 3; i++) {
		a = a + omp_get_thread_num();
		b = b + 2*omp_get_thread_num();
		printf("a = %d, b = %d\n",a,b);
	}
	printf("golobal: i = %d, a = %d, b = %d\n",i,a,b);
	printf("#########################################################\n");

	#pragma omp parallel
	for (i = 0; i < 3; i++) {
		printf("1: i = %d, id = %d\n",i, omp_get_thread_num());
	}

	#pragma omp parallel for
	for (i = 0; i < 3; i++) {
		printf("2: i = %d\n",i);
	}
	printf("#########################################################\n");

	int jobs;
	#pragma omp parallel
	{
		printf("ID = %d\n", omp_get_thread_num());
		#pragma omp for
		for (i = 0; i < 5; i++) {
			printf("id = %d\n",omp_get_thread_num());
		}
	}
	return 0;
}
