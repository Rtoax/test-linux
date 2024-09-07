/**
 * Testing div instructions
 *
 * Compile macros:
 * : DEBUG: Debug mode
 * : IGNORE_RETURN_VALUE: Get return value
 */
#include <stdio.h>
#include <stdlib.h>

#if defined(__aarch64__)
static inline void arch_asm_udiv(void)
{
	unsigned long a, b;
# if !defined(IGNORE_RETURN_VALUE)
	unsigned long ret;
# endif

	a = 1024;
	b = 512;

	__asm__("udiv x1, %[a], %[b] \n\t"
# if !defined(IGNORE_RETURN_VALUE)
		"mov %[ret], x1 \n\t"
		: [ret] "=r"(ret)
# else
		:
# endif
		: [a] "r"(a), [b] "r"(b));

# if defined(DEBUG) && !defined(IGNORE_RETURN_VALUE)
	printf("ret = %ld\n", ret);
# endif
}

#elif defined(__x86_64__)

static inline void arch_asm_div(void)
{
	unsigned long a, b;
# if !defined(IGNORE_RETURN_VALUE)
	unsigned long ret, mod;
# endif

	a = 1024;
	b = 512;

	__asm__("mov %[a], %%rax \n\t"
		"xor %%edx, %%edx \n\t"
		"div %[b] \n\t"
# if !defined(IGNORE_RETURN_VALUE)
		"mov %%rax, %[ret] \n\t"
		"mov %%rdx, %[mod] \n\t"
		: [ret] "=r"(ret), [mod] "=r"(mod)
# else
		:
# endif
		: [a] "r"(a), [b] "r"(b)
		: "%rax", "rcx");

# if defined(DEBUG) && !defined(IGNORE_RETURN_VALUE)
	printf("ret = %ld, mod = %ld\n", ret, mod);
# endif
}
/* TODO: x86 has udiv too. */
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
