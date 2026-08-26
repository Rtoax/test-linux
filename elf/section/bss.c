#include <stdio.h>

static int i; /* .bss */
static int big_arr1[4096 * 1024]; /* .bss */
int big_arr2[4096 * 1024]; /* .bss */

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
	(void)big_arr1;
	return 0;
}
