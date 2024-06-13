#include <stdio.h>

int main(void)
{
#if defined(__x86_64__)
	printf("__x86_64__\n");
#elif defined(__aarch64__)
	printf("__aarch64__\n");
#elif defined(__sw_64__)
	printf("__sw_64__\n");
#else
# pragma GCC error "No support arch\n"
#endif
	return 0;
}
