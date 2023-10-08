#include <stdio.h>

int main(void)
{
#define P(v)	printf("%-32s = %#016lx\n", #v, v);

	P(1L);
	P(0xffffL ^ 0x1111);

	return 0;
}
