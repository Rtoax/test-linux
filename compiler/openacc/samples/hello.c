#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int i;

	#pragma acc parallel
	for (i = 0; i < 10; i++) {
		printf("i = %d\n", i);
	}
	return 0;
}
