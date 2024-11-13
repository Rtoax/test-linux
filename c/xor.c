#include <stdio.h>

int main(void)
{
#define P(v)	printf("%-32s = %#016lx\n", #v, v);

	P(1L);
	P(0xFL ^ 1L);
	P(0xffffL ^ 0x1111L);

	return 0;
}
