/**
 *	BTS: bit test and set
 *
 *	https://www.felixcloutier.com/x86/bts
 *	https://stackoverflow.com/questions/1983303/using-bts-assembly-instruction-with-gcc-compiler
 */
#include <stdio.h>
#include <stdbool.h>

typedef unsigned long LongWord;

static inline void SetBit(LongWord* array, const int bit)
{
	asm("bts %1,%0" : "+m" (*array) : "r" (bit));
}

int main(void)
{
	LongWord l = 0;
	SetBit(&l, 0);
	printf("0x%lx\n", l);
}
