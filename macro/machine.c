#include <stdio.h>

int main(void)
{
#if !defined(__clang__)
# if #machine(__linux__)
	printf("Linux");
# endif
#endif
	return 0;
}
