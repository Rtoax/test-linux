#include <stdio.h>

#if defined(__x86_64__)
# pragma GCC target("no-avx")
#endif
int fun(void)
{
	printf("fun\n");
	return 0;
}

int main(void)
{
	fun();
	printf("main\n");
	return 0;
}
