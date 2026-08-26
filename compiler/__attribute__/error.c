#include <stdio.h>

#define __error __attribute__((error("Symbol is not public ABI")))

#ifdef ERROR
__error
#endif
void func1(void)
{
	printf("funcs\n");
}

int main(void)
{
	func1();
	return 0;
}
