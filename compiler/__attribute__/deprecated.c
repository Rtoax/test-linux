#include <stdio.h>
#include "compiler.h"

__deprecated void print_something(void)
{
	printf("print_something.\n");
}

int main(void)
{
	print_something();
	return 0;
}
