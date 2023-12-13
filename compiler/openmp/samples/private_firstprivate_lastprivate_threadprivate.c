#include <stdio.h>
#include <omp.h>

int count = 0;

int main(void)
{
	int incr, i, j, id, nd;
	incr = 0;

	#pragma omp parallel for reduction(+:incr)
	for (i = 0; i < 10; i++) {
		id = omp_get_thread_num();
		nd = omp_get_num_threads();
		incr += i;
		printf("incr = %d, id = %d/%d\n",incr,id,nd);
	}
	printf("#incr = %d\n",incr);
	printf("#####################################################\n");

	incr = 0;
	#pragma omp parallel for firstprivate(incr)
	for (i = 2; i < 10; i++) {
		id = omp_get_thread_num();
		nd = omp_get_num_threads();
		incr = i;
		printf("incr = %d, id = %d/%d\n",incr,id,nd);
	}
	printf("#incr = %d\n",incr);
	printf("#####################################################\n");

	incr = 0;
	#pragma omp parallel for lastprivate(incr)
	for (i = 2; i < 10; i++) {
		id = omp_get_thread_num();
		nd = omp_get_num_threads();
		incr = i;
		printf("incr = %d, id = %d/%d\n",incr,id,nd);
	}
	printf("#incr = %d\n",incr);
	printf("#####################################################\n");

	int X = 13;
	#pragma omp parallel for private(X)
	for (i = 0; i < 5; i++) {
		X += i;
		printf("X = %d\n",X);
	}
	printf("#X = %d\n",X);
	printf("############\n");
	X = 13;
	#pragma omp parallel for firstprivate(X) lastprivate(X)
	for (i = 0; i < 5; i++) {
		X += i;
		printf("X = %d\n",X);
	}
	printf("#X = %d\n",X);
	printf("#####################################################\n");

	#pragma omp parallel for private(j)
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			printf("( %d , %d )\n",i,j);
		}
	}
	printf("#####################################################\n");

	int v = 3;
	i = 0;
	#pragma omp parallel for firstprivate(v) lastprivate(v)
	for (i = 1; i <= 5; i++) {
		printf("up: i = %d, v = %d\n",i,v);
		if (i == 5)
			v = 13;
		printf("down: i = %d, v = %d\n",i,v);
	}
	printf(" out: i = %d, v = %d\n",i,v);
	printf("#####################################################\n");

	#pragma omp threadprivate(count)
	#pragma omp parallel
	for (i = 0; i < 50; i++) {
		#pragma omp critical
		count++;
		printf("i = %2d, count = %2d, id = %2d/%2d\n",i,count,omp_get_thread_num(), omp_get_num_threads());
	}
	printf("O: i = %2d, count = %2d, id = %2d/%2d\n",i,count,omp_get_thread_num(), omp_get_num_threads());
	return 0;
}
