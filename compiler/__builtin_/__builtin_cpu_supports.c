#include <stdio.h>

#pragma GCC target "mmx"
void print_mmx(void)
{
	printf("\nI got MMX !\n");
}

int main(void)
{
#if defined(__x86_64__) || defined(__i386__)
	if (__builtin_cpu_supports("mmx")) {
		printf("\nI got MMX !\n");
	} else {
		printf("\nWhat ? MMX ? What is that ?\n");
	}
#else
# error "Not support __builtin_cpu_supports but x86."
#endif

	print_mmx();

	return (0);
}