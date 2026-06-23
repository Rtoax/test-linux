#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *str = "123abc";
	char *ret;
	long int li = strtol(str, &ret, 10);

	printf("%s : %ld, %s\n", str, li, ret);

	return 0;
}
