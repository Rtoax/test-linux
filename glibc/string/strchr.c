#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>

int main(void)
{
	char *str = "rongtao zaima";
	printf("%s\n", strchr(str, 't'));

	return 0;
}
