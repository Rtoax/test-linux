#include <stdio.h>

int addi(int v, int i)
{
	return v + i;
}

int main(void)
{
	int i, total;

	total=0;

	for (i = 0; i < 10; i++) {
		total += addi(total, i);
	}

	if (total != 45) {
		printf("failure.\n");
	} else {
		printf("success.\n");
	}

	return 0;
}
