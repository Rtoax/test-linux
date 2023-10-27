#include <stdio.h>
#include "byteswap.h"

int main(void)
{
	unsigned long l = 0xffff000012345678UL;
	printf("%lx -> %lx\n", l, byteswap64(l));
	return 0;
}
