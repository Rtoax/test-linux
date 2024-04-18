#include <omp.h>
#include <stdio.h>

int main(void)
{
	omp_lock_t lock;
	omp_init_lock(&lock);
	omp_set_lock(&lock);
	omp_unset_lock(&lock);
	return 0;
}
