#include <stdio.h>

void daxpy(double *x, double *y, double a, int n);
void daxpy_sve(double *x, double *y, double a, int n);

int main(void)
{
	double x[] = {1, 2, 3, 4};
	double y[] = {1, 2, 3, 4};
	daxpy(x, y, 2, 3);
	return 0;
}
