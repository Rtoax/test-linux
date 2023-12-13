#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
	int i, j, id;
	int sum = 0;

	#pragma omp parallel for shared(sum)
	for (j = 0; j < 5; j++) {
		#pragma omp atomic
		sum++;
		printf("j = %d, id = %d, sum = %d\n",j,omp_get_thread_num(),sum);
	}
	printf("sum = %d\n",sum);
}
