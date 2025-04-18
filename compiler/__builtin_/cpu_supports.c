#include <stdio.h>

#if defined(__x86_64__) || defined(__i386__)
#pragma GCC target "mmx"
void print_mmx(void)
{
	printf("\nI got MMX !\n");
}
#else
void print_mmx(void) {}
#endif

int main(void)
{
#if defined(__x86_64__) || defined(__i386__)
	if (__builtin_cpu_supports("mmx")) {
		printf("\nI got MMX !\n");
	} else {
		printf("\nWhat ? MMX ? What is that ?\n");
	}
#elif defined(__aarch64__) || defined(__arm__)
# warning "TODO: arm"
#elif defined(__sw_64__) || defined(__riscv)
# warning "TODO: sw"
#else
# error "Not support __builtin_cpu_supports but x86, arm."
#endif

	print_mmx();

	return (0);
}

