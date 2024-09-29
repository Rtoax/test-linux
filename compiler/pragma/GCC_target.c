#include <stdio.h>

#if defined(__x86_64__)
# if defined(__clang__)
#  pragma message "clang not support target"
# elif defined(__GNUC__)
#  pragma GCC target("no-avx")
# endif
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
