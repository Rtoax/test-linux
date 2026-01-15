#include <stdio.h>

void daxpy(double *x, double *y, double a, int n)
{
	int i;
	for (i = 0; i < n; i++)
		y[i] = a * x[i] + y[i];
}

int main(void)
{
	double x[] = { 1, 2, 3, 4, 5 };
	double y[] = { 1, 2, 3, 4, 5 };
	daxpy(x, y, 3, 5);
	return 0;
}
