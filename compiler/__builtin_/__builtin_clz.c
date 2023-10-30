#include <stdio.h>

int main(int argc, char *argv[])
{
	int i;
	for (i = 0; i < 100; i++)
		printf("0x%0x, %d\n", i, __builtin_clz(i));

	return 0;
}