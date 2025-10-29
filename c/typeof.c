#include <stdio.h>

int main(void)
{
	int i1, i2;
	typeof(i1 + i2) i3;

	printf("size of i3 is %ld\n", sizeof(i3));

	return 0;
}
