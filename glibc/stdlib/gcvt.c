#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


int main(void)
{
	char buf[64];

	/* convert a floating-point number to a string */
	gcvt(123.123, 6, buf);
	printf("%s\n", buf);

	return 0;
}
