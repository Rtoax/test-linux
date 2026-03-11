#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

/* write(1, "Hello\n", 6) */
#define ASM_WRITE_HELLO_X86_64() ({	\
	__asm__("mov $0x1, %al\n"	\
		"mov %al, %dil\n"	\
		"push $0x00000a6f\n"	\
		"push $0x6c6c6548\n"	\
		"mov %rsp, %rsi\n"	\
		"mov $0xa, %dl\n"	\
		"syscall\n"		\
		"pop %rsi\n"		\
		"pop %rsi\n");		\
})

void asm_write_stack(void)
{
	ASM_WRITE_HELLO_X86_64();
}

int asm_write(void)
{
	int ret;
	int fd = 1;
	char msg[] = {"Hello\n"};
	size_t len = 6;

	__asm__("mov %[fd], %%edi \n\t"
		"movq %[msg], %%rsi \n\t"
		"movq %[len], %%rdx \n\t"
		"movq $1, %%rax \n\t"
		"syscall \n\t"
		: "=r"(ret)
		: [fd] "r"(fd), [msg] "r"(msg), [len] "r"(len));
	return ret;
}

int main(void)
{
/**
 * Test stackoverflow of asm_write()
 */
#ifdef INFINITE_LOOP
	while (1) {
#endif
		asm_write();
		asm_write_stack();
#ifdef INFINITE_LOOP
	}
#endif
	printf("exit.\n");
	return 0;
}
