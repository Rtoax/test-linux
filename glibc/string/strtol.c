#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void)
{
	char *ret;

	long int li = strtol("123abc", &ret, 10);

	printf("%ld, %s\n", li, ret);

	return 0;
}
