#include <math.h>
#include <stdio.h>

static double ds[] = { 1, 2, 3, 3.14 };

int main(int argc, char *argv[])
{
	for (int i = 0; i < sizeof(ds) / sizeof(ds[0]); i++)
		printf("exp2(%lf) = %lf\n", ds[i], exp2(ds[i]));

	return 0;
}
