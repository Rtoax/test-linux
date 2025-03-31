#include <stdio.h>

#include "unused.h"

int main(void)
{
	int __unused *p = NULL;

#if defined(__i386__)
	printf("x86-32\n");
	printf("sizeof(*) = %d\n", sizeof(p));
#elif defined(__x86_64__)
	printf("x86-64\n");
	printf("sizeof(*) = %ld\n", sizeof(p));
#elif defined(__aarch64__)
	printf("aarch64\n");
	printf("sizeof(*) = %ld\n", sizeof(p));
#elif defined(__riscv)
# if __riscv_xlen == 64
	printf("riscv64\n");
	printf("sizeof(*) = %ld\n", sizeof(p));
# else
	printf("riscv32\n");
# endif
#elif defined(__loongarch64)
	printf("loongarch64\n");
	printf("sizeof(*) = %ld\n", sizeof(p));
#endif
	return 0;
}
