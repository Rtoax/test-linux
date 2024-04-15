#include <stdio.h>

int main(void)
{
#if defined(__x86_64__)
	printf("__x86_64__\n");
#else
#pragma GCC error "__x86_64__ is not defined\n"
#endif
	return 0;
}
