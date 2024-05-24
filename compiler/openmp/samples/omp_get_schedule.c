#include <omp.h>
#include <stdio.h>

int main(void)
{
	/**
	 * omp_schedule(omp_sched_t * kind, int *modifier);
	 * Reference: OpenMP specifications v3.0, section 3.2.12.
	 */
	omp_sched_t kind;
	int modifier;
	omp_get_schedule(&kind, &modifier);
	printf("omp_get_schedule modifier = %d\n", modifier);
	return 0;
}
