#include <omp.h>
#include <stdio.h>

int main(void)
{
	omp_set_num_threads(6);
	#pragma omp parallel for
	for (int i = 0; i < 10; i++) {
		printf("%d, %d/%d\n", i, omp_get_thread_num(), omp_get_num_threads());
	}
	return 0;
}
