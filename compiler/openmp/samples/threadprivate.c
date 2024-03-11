#include <stdio.h>
#include <omp.h>
#include <pthread.h>

int counter = 0;
#pragma omp threadprivate(counter)

int increment_counter(void)
{
	counter++;
	return counter;
}

int increment_counter2(void)
{
	static int counter = 0;
	#pragma omp threadprivate(counter)

	counter++;
	return counter;
}

int main(void)
{
	printf("%d\n", increment_counter());
	printf("%d\n", increment_counter2());

	return 0;
}
