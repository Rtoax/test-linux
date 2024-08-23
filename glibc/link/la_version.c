#define _GNU_SOURCE
#include <link.h>
#include <stdio.h>

int main(void)
{
	printf("la_version %d\n", la_version(0));
	return 0;
}
