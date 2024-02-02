#include <stdio.h>

#include "unused.h"

int main(void)
{
	int __unused *p = NULL;

#if defined(__i386__)
	printf("x86-32\n");
#elif defined(__x86_64__)
	printf("x86-64\n");
#elif defined(__aarch64__)
	printf("aarch64\n");
#endif
	printf("sizeof(*) = %ld\n", sizeof(p));
	return 0;
}
