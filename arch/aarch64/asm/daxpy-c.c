#include <stdio.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

void daxpy(double *x, double *y, double a, int n);
void daxpy_sve(double *x, double *y, double a, int n);

int main(void)
{
#define ELEMS 1,2,3,4,5,6,7,8,9,0,
	int i;
	double x[] = {ELEMS};
	double y[] = {ELEMS};
	double a = 2;
	int n = ARRAY_SIZE(x);

	daxpy(x, y, a, n);

	for (i = 0; i < n; i++) {
		printf("%lf,", y[i]);
	} printf("\n");
	return 0;
}
