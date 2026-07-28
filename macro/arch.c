#include <stdio.h>
#include "unused.h"

int main(void)
{
	int __unused *p = NULL;

#if defined(__i386__)
	printf("x86-32 ");
	printf("sizeof(*) = %d\n", sizeof(p));
#elif defined(__x86_64__)
	printf("x86-64 ");
	printf("sizeof(*) = %ld\n", sizeof(p));
#elif defined(__aarch64__)
	printf("aarch64 ");
	printf("sizeof(*) = %ld\n", sizeof(p));
#elif defined(__riscv)
# if __riscv_xlen == 64
	printf("riscv64 ");
# else
	printf("riscv32 ");
# endif
	printf("sizeof(*) = %ld\n", sizeof(p));
#elif defined(__loongarch64)
	printf("loongarch64 ");
	printf("sizeof(*) = %ld\n", sizeof(p));
#elif defined(__powerpc64__)
#if defined(__PPC64__)
	printf("__PPC64__: ");
#endif
	printf("ppc64 ");
	printf("sizeof(*) = %ld\n", sizeof(p));
#elif defined(__s390x__)
	printf("s390x ");
#if defined(__s390__)
	printf("(s390) ");
#endif
	printf("sizeof(*) = %ld\n", sizeof(p));
#endif
	return 0;
}
