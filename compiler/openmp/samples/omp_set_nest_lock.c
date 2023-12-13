#include <stdio.h>
#include <omp.h>

int main(void)
{
	omp_nest_lock_t lock;
	int count = 0, i;

	#pragma omp parallel
	printf("id = %d\n",omp_get_thread_num());

	#pragma omp parallel for
	for (i = 0; i < 13; i++) {
		omp_set_nest_lock(&lock);
		printf("count = %d\n", count++);
		omp_unset_nest_lock(&lock);
	}
}
