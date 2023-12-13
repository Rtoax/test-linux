#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
#include <omp.h>
#endif

/* shared */
int gval = 8;

/* z: private */
void funcb(int *x, int *y, int z)
{
	int u;
	u = (*y)*gval;
	*x = u + z;
}

void funca(int *a, int n)
{
	int i;
	int cc = 9;
	#pragma omp parallel for
	for (i = 0; i < n; i++) {
		int temp = cc;
		funcb(&a[i], &temp, i);
	}
}

int main(int argc, char *argv[])
{
	int n = 10;
	int *a = malloc(sizeof(int)*n);
	funca(a,n);
	return 0;
}
