#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	unsigned char ch = __builtin_read8("abc");

	printf("ch = %c\n", ch);

	return 0;
}