#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void loadavg(void)
{
	float exp_1 = 1.0 / exp(5.0 / 60.0) * 2048;
	float exp_5 = 1.0 / exp(5.0 / 300.0) * 2048;
	float exp_15 = 1.0 / exp(5.0 / 900.0) * 2048;

	printf("%f\n", exp_1);
	printf("%f\n", exp_5);
	printf("%f\n", exp_15);
}

int main(int argc, char *argv[])
{
	loadavg();

	for (int i = 1; i < argc; i++) {
		double d = strtod(argv[i], NULL);
		printf("exp(%lf) = %lf\n", d, exp(d));
	}

	return 0;
}
