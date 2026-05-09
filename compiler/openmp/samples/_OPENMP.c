/**
 * _OPENMP:
 * 200505：OpenMP 2.5
 * 200805：OpenMP 3.0
 * 201107：OpenMP 3.1
 * 201307：OpenMP 4.0
 * 201511：OpenMP 4.5
 * 201811：OpenMP 5.0
 * 202011：OpenMP 5.1
 * 202111：OpenMP 5.2
 */
#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
	printf("_OPENMP = %d\n", _OPENMP);
	return 0;
}
