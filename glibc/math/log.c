#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef LOG10
#define log(x) log10(x)
#define NAME "log10"
#elif defined(LOG2)
#define log(x) log2(x)
#define NAME "log2"
#elif defined(LOGB)
#define log(x) logb(x)
#define NAME "logb"
#else
#define NAME "log"
#endif

static double ds[] = { 1, 2, M_E, 3, 3.14, 4, 8, 10, 16, 1e2, 1E10 };

int main(int argc, char *argv[])
{
	double v, x;

	x = M_E;

#if defined(STRESS)
	while (1)
#endif
		v = (volatile typeof(v))log(x);

	printf(NAME "(%lf) = %lf\n", x, v);

	for (int i = 0; i < sizeof(ds) / sizeof(ds[0]); i++)
		printf(NAME "(%lf) = %lf\n", ds[i], log(ds[i]));

	return 0;
}
