#include <stdio.h>

static inline long get_current()
{
	register unsigned long sp asm("sp");
	return sp;
}

int main()
{
	printf("%ld\n", get_current());
}
