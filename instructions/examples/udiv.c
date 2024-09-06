#include <stdio.h>
#include <stdlib.h>

#if defined(__aarch64__)
static inline void arch_asm_udiv(void)
{
	unsigned long a, b;

	a = 1024;
	b = 512;

	__asm__("udiv x1, %[a], %[b] \n\t"
		: : [a] "r"(a), [b] "r"(b));
}
#elif defined(__x86_64__)
static inline void arch_asm_div(void)
{
	unsigned long a, b, ret;

	a = 1024;
	b = 512;

	__asm__("mov %[a], %%rax \n\t"
		"xor %%edx, %%edx \n\t"
		"div %[b] \n\t"
		: "=r"(ret)
		: [a] "r"(a), [b] "r"(b));
}
# define arch_asm_udiv() arch_asm_div()
#else
# warning "Not support arch for udiv"
# define arch_asm_udiv() fprintf(stderr, "not support udiv of this program.\n")
#endif

void asm_udiv(void)
{
	arch_asm_udiv();
}

int main(int argc, char *argv[])
{
	unsigned long n = 1500000000;

	if (argc > 1)
		n = strtoull(argv[1], NULL, 10);

	fprintf(stderr, "Usage: %s [n=%ld]\n", argv[0], n);

	while (n--) {
		asm_udiv();
	}

	return 0;
}
