#include <stdio.h>

int main(void)
{
	int i;
	for (i = 0; i < 256; i++)
		printf("%4d : %c\n", i, i);
}
