#include <stdio.h>

#define ASM1_x86_64()                  \
	__asm__("push   $0x44434241\n" \
		"mov    %rsp,%rdi\n"   \
		"call   puts\n"        \
		"pop    %rsi\n")

#define ASM2_x86_64()                  \
	__asm__("sub    $8, %%rsp\n"   \
		"push   $0x44434241\n" \
		"mov    %%rsp,%%rdi\n" \
		"call   puts\n"        \
		"add    $16, %%rsp\n"  \
		:                      \
		:                      \
		: "rdi", "memory")

static char abcd[] = { "ABCD" };

void puts_asm1(void)
{
#if defined(__x86_64__)
	ASM1_x86_64();
#elif defined(__i386__)
#endif
}

void puts_asm2(void)
{
#if defined(__x86_64__)
	ASM2_x86_64();
#elif defined(__i386__)
#endif
}

int main(void)
{
#if defined(__x86_64__)
	ASM1_x86_64(); /* segv on ubuntu 22.04 */
	ASM2_x86_64();
#elif defined(__i386__)
#endif

	puts(abcd);
	puts("ABCD");
	puts_asm1();
	puts_asm2();
	return 0;
}
