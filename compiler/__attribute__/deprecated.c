#include <stdio.h>


#define __deprecated  __attribute__((deprecated("Symbol is not yet part of stable ABI")))

__deprecated void print_something(void)
{
	printf("print_something.\n");
}

int main(void)
{
	print_something();
	return 0;
}
