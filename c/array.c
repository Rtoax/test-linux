#include <stdio.h>

int main(void)
{
	int array[2][3];

	printf("%p\n", &array[0][0]);
	printf("%p\n", &array[1][0]);
	printf("%p\n", &array[0][1]);
	printf("%p\n", &array[0][3]);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
	printf("%p\n", &array[3][0]);
	printf("%p\n", array[3]);
#pragma GCC diagnostic pop

	return 0;
}
