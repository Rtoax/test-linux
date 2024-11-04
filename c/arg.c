#include <stdio.h>


int bar(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
	return 0xff;
}

int foo(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
	return bar(a1, a2, a3, a4, a5, a6, a7, a8);
}

int main(void)
{
	int ret;

	ret = foo(1, 2, 3, 4, 5, 6, 7, 8);

	(void)ret;

	return 0;
}
