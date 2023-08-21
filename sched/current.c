#include <stdio.h>


static inline unsigned long get_current(void)
{
	register unsigned long sp asm("sp");
	return sp;
}

int main(void)
{
	printf("0x%lx\n", get_current());
	return 0;
}
