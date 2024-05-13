#include <stdio.h>

int main(void)
{
	volatile char c = 0x80;
	unsigned u;
	int i;

	u = c;
	i = c;

	printf("c = %d, u = %u, i = %d\n", c, u, i);

	return 0;
}
