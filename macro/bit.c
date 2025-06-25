#include <stdio.h>
#include "bit.h"

int main(void)
{
	int i = 0x00f1;
	printf("%d, %x, %s\n", i, i, itobs(7, i));
	return 0;
}
