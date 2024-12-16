#include <stdio.h>

#define ALLOW_INTERNAL_API
#ifndef ALLOW_INTERNAL_API
#define __rte_internal \
__attribute__((error("Symbol is not public ABI"), \
section(".text.internal")))
#else
#define __rte_internal \
__attribute__((section(".text.internal")))
#endif

void __rte_internal func1(void)
{
	printf("funcs\n");
}

int main(void)
{
	func1();
	return 0;
}