#include <stdio.h>
#include <stdint.h>
#include <byteswap.h>

int main(void)
{
	int16_t i = 1;
	printf("%d\n", i);
	printf("%d\n", bswap_16(i));
	printf("%d\n", __bswap_constant_16(i));
	return 0;
}
