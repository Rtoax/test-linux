#include <stdio.h>

static int i;

int *foo(void)
{
	static int *int_ptr;	/* .bss */
	if (!int_ptr)
		int_ptr = &i;
	return int_ptr;
}

int main(void)
{
	int *p = foo();
	(void)p;
	return 0;
}
