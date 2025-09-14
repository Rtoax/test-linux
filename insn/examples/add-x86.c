#include <stdio.h>

/* kernel arch/x86/include/asm/checksum_64.h */
static inline unsigned add32_with_carry(unsigned a, unsigned b)
{
	asm("addl %2,%0\n\t"
	    "adcl $0,%0"
	    : "=r" (a)
	    : "0" (a), "rm" (b));
	return a;
}

int main(void)
{
	unsigned a, b, c;

	a = 2;
	b = 3;

	c = add32_with_carry(a, b);
	printf("c = %d\n", c);

	return 0;
}
