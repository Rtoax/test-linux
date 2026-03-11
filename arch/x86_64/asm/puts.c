#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>


void puts_stack(void)
{
	char msg[] = {"1234567890"};
	puts(msg);
}

void asm_puts_stack_1(void)
{
	/**
	 * FIXME: Why print 'Hell'?
	 */
	__asm__("push $0x6f\n"
		"push $0x6c6c6548\n"
		"mov %rsp, %rdi\n"
		"call puts\n"
		"pop %rdi\n"
		"pop %rdi\n");
}

void asm_puts_stack(void)
{
	__asm__("push %rax\n"
		"mov $0x0000006f6c6c6548, %rax\n"
		"push %rax\n"
		"mov %rsp, %rdi\n"
		"call puts\n"
		"pop %rax\n"
		"pop %rax\n");
}

int main(void)
{
#define C(c) printf("%-8s : 0x%x\n", #c, c);
	C('H');
	C('e');
	C('l');
	C('l');
	C('o');
	C('\n');
#undef C

	puts_stack();
	asm_puts_stack_1();

/**
 * Test stackoverflow
 */
#ifdef INFINITE_LOOP
	while (1)
#endif
		asm_puts_stack();
	printf("exit.\n");
	return 0;
}
