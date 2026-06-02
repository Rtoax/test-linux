#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef LOG10
#define log(x) log10(x)
#endif

static double ds[] = { 1, 2, M_E, 3, 3.14, 10, 1e2, 1E10 };

int main(int argc, char *argv[])
{
	double v, x;

	x = M_E;

#if defined(STRESS)
	while (1)
#endif
		v = (volatile typeof(v))log(x);

	printf("log(%lf) = %lf\n", x, v);

	for (int i = 0; i < sizeof(ds) / sizeof(ds[0]); i++)
		printf("log(%lf) = %lf\n", ds[i], log(ds[i]));

	return 0;
}
