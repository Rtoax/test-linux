#include <stdio.h>
#include <stdint.h>

#if __WORDSIZE == 64
#define Paddr "%ld"
typedef uint64_t addr_t;
#else
#define Paddr "%d"
typedef uint32_t addr_t;
#endif

int main(void)
{
	printf("__WORDSIZE = %d\n", __WORDSIZE);
	printf("size of addr_t "Paddr"\n", sizeof(addr_t));

	return 0;
}
