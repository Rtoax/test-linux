#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
	int i;
	int count1, count2;

	count1 = count2 = 0;

	omp_set_num_threads(10);

	#pragma omp parallel for
	for (i = 0; i < 25; i++) {
		#pragma omp critical
		count1++;
		count2++;
	}
	printf("count1 = %d, count2 = %d\n", count1, count2);

	#pragma omp parallel for
	for (i = 0; i < 25; i++) {
		#pragma omp atomic
		count1--;
		count2--;
	}
	printf("count1 = %d, count2 = %d\n", count1, count2);
	return 0;
}
