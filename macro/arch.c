#include <stdio.h>
#include "unused.h"

int main(void)
{
#if defined(__i386__)
	printf("x86-32 ");
#elif defined(__x86_64__)
	printf("x86-64 ");
#elif defined(__aarch64__)
	printf("aarch64 ");
#elif defined(__riscv)
# if __riscv_xlen == 64
	printf("riscv64 ");
# else
	printf("riscv32 ");
# endif
#elif defined(__loongarch64)
	printf("loongarch64 ");
#elif defined(__powerpc64__)
	printf("ppc64 ");
#if defined(__PPC64__)
	printf("(PPC64) ");
#endif
#elif defined(__s390x__)
	printf("s390x ");
#if defined(__s390__)
	printf("(s390) ");
#endif
#endif

#define szof(x) printf("%s = %d\n", #x, (int)x);
	szof(sizeof(void *));

	return 0;
}
