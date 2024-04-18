#include <omp.h>
#include <stdio.h>

int main(void)
{
	omp_nest_lock_t lock;
	omp_init_nest_lock(&lock);
	omp_set_nest_lock(&lock);
	omp_test_nest_lock(&lock);
}
