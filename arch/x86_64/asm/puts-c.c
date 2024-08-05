#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>


void asm_puts_stack(void)
{
	/**
	 * FIXME: Why print 'Hell'?
	 */
	__asm__("push $0x00000a6f\n"
		"push $0x6c6c6548\n"
		"mov %rsp, %rdi\n"
		"call puts\n"
		"pop %rdi\n"
		"pop %rdi\n");
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
