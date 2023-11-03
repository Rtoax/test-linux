#include <stdio.h>

int main(void)
{
#ifdef __clang__
	printf("clang:\n");
#endif
	return 0;
}
