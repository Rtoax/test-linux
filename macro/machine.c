#include <stdio.h>

int main(void)
{
#if #machine(__linux__)
	printf("Linux");
#endif
	return 0;
}
