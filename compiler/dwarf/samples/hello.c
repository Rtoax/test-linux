/**
 * hello.c - For test dwarf
 */
#include <stdio.h>

int foo(int i)
{
	return i * 2;
}

int main(int argc, char *argv[])
{
	char *strp1 = "Hello World";
	char *strp2 = strp1;
	char *strp_sup = strp1 + 6;

	printf("%s\n", strp1);
	printf("%d\n", foo(1024));
	return 0;
}
