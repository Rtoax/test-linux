#include <stdio.h>

int main(void)
{
#define Pxl(v) printf("%-16s : %#016lx\n", #v, (unsigned long)v)

	Pxl(0x111 ^ 0x101);
	Pxl(0x011 ^ 0x101);

#undef Pxl
	return 0;
}
