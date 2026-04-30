#include <stdio.h>

long negative(long v)
{
	long r2 = v;
	long r3 = r2;
	r3 <<= 32;
	r3 >>= 63;
	r2 ^= r3;
	r2 -= r3;
	r3 = r2;
	r3 <<= 32;
	r3 >>= 32;
#ifdef DEBUG
	printf("v=%ld(%#lx) r2=%ld(%#lx) r3=%ld(%#lx)\n", v, v, r2, r2, r3, r3);
#endif
	return r3;
}

int main(void)
{
#define Pxl(v) printf("%-16s : %#016lx\n", #v, (unsigned long)v)

	Pxl(0x111 ^ 0x101);
	Pxl(0x011 ^ 0x101);
	Pxl(negative(-1));
	Pxl(negative(-0xff));
	Pxl(negative(-0x1234567890));
	Pxl(negative(2));

#undef Pxl
	return 0;
}
