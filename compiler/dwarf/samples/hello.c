/**
 * hello.c - For test dwarf
 *
 * 2022-01-24	Rong Tao	Create this.
 */
#include <stdio.h>

int main(int argc, char *argv[])
{
	char *strp1 = "Hello World";
	char *strp2 = strp1;
	char *strp_sup = strp1 + 6;

	printf("%s\n", strp1);
	return 0;
}

