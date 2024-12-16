#include <stdio.h>


#define __gnu_inline __attribute__((__gnu_inline__))

inline __gnu_inline
int fun(void)
{
	printf("-------\n");
}

int main(void)
{
	fun();
	return 0;
}
