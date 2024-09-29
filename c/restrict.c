#include <stdio.h>


int foo(int * restrict p)
{
	int *ip = p;
	*ip = 18;
	return 0;
}

int main(void)
{
	int a = 0;
	foo(&a);
	return 0;
}
