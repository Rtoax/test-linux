#include <stdio.h>

int foo(void)
{
	printf("helloworld\n");
	return 0;
}

int main(void)
{
	#pragma custom io_volatile(on)

	#pragma call foo()

	return 0;
}
