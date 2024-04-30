#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

int main(void)
{
	float f, s;
	int i;

	for (i = -5; i < 5; i++) {
		f = 1.0 / i;
		s = f / i;

		if (isinf(f))
			printf(" isinf: %d\n", i);
		if (isinfl(f))
			printf("isinfl: %d\n", i);
		if (isinff(f))
			printf("isinff: %d\n", i);

		if (isnan(s))
			printf(" isnan: %d\n", i);
		if (isnanf(s))
			printf("isnanf: %d\n", i);
		if (isnanl(s))
			printf("isnanl: %d\n", i);

		if (isfinite(f))
			printf("isfinite: %d\n", i);
		if (isnormal(f))
			printf("isnormal: %d\n", i);

		if (finite(f))
			printf(" finite: %d\n", i);
		if (finitef(f))
			printf("finitef: %d\n", i);
		if (finitel(f))
			printf("finitel: %d\n", i);
	}

	return 0;
}
