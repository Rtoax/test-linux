#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	double ds[] = { 1, 2, M_E, 3, 3.14, 4, 8, 10, 16, 1e2, 1E10 };

	for (int i = 0; i < sizeof(ds) / sizeof(ds[0]); i++)
		printf("powf(%lf) = %lf\n", ds[i], powf(ds[i], 2));

	return 0;
}
