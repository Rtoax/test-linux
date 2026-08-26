#include <stdio.h>

static int i; /* .bss */
static int big_arr[4096 * 1024];

int *foo(void)
{
	static int *int_ptr; /* .bss */
	if (!int_ptr)
		int_ptr = &i;
	return int_ptr;
}

int main(void)
{
	int *p = foo();
	(void)p;
	(void)big_arr;
	return 0;
}
