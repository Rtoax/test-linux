#include <stdio.h>
#include <malloc.h>

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)
#define bswap16(x) __builtin_bswap16(x)
#endif

#define bswap32(x) __builtin_bswap32(x)

#define bswap64(x) __builtin_bswap64(x)


int main(void)
{
	unsigned short us = 0x1234;
	unsigned int ui = 0x12345678;
	unsigned long ul = 0x1234567801020304;

	printf("bswap16(%x) = %x\n", us, bswap16(us));
	printf("bswap32(%x) = %x\n", ui, bswap32(ui));
	printf("bswap64(%lx) = %lx\n", ul, bswap64(ul));

	return 0;
}