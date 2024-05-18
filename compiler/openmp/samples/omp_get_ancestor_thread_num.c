#include <omp.h>
#include <stdio.h>

int main(void)
{
	int i = omp_get_active_level();
	printf("omp_get_active_level = %d\n", i);
	int nthread = omp_get_ancestor_thread_num(i);
	printf("omp_get_ancestor_thread_num = %d\n", nthread);
	return 0;
}
