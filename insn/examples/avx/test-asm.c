#include <stdio.h>
#include <stdalign.h>

int test_asm(int a, int b, int out[]);

int main(void)
{
	int ret, i;
	alignas(64) int buffer[16];

	ret = test_asm(1, 1, buffer);
	for (i = 0; i < 16; i++)
		printf("0x%08x\n", buffer[i]);

	return ret;
}
