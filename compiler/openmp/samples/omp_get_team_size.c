#include <omp.h>
#include <stdio.h>

int main(void)
{
	int i = omp_get_level();
	i = omp_get_team_size(i);
	printf("omp_get_team_size = %d\n", i);
	return 0;
}
