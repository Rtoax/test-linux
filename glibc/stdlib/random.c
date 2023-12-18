#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void)
{
	RAND_MAX;

	srandom((int)time(0));

	int i, j;
	for (i = 1; i <= 3000; i++) {
		j = 1 + (int)(10.0 * random() / RAND_MAX + 1.0);
		printf("%3d", j);
		if (i % 30 == 0)
		printf("\n");
	}

	return 0;
}
