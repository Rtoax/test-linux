#include <string.h>
#include <stdio.h>

#define ASM_WRITE_HELLO_AARCH64() ({		\
	__asm__("stp x29, x30, [sp, #-32]!\n"	\
		"mov x29, sp\n"			\
		"str xzr, [sp, #16]\n"		\
		"mov w0, #0x48\n"		\
		"strb w0, [sp, #16]\n"		\
		"mov w0, #0x65\n"		\
		"strb w0, [sp, #17]\n"		\
		"mov w0, #0x6c\n"		\
		"strb w0, [sp, #18]\n"		\
		"mov w0, #0x6c\n"		\
		"strb w0, [sp, #19]\n"		\
		"mov w0, #0x6f\n"		\
		"strb w0, [sp, #20]\n"		\
		"mov w0, #0xa\n"		\
		"strb w0, [sp, #21]\n"		\
		"add x0, sp, #0x10\n"		\
		"str x0, [sp, #24]\n"		\
		"\n"				\
		"mov x0, #1\n"			\
		"ldr x1, [sp, #24]\n"		\
		"mov x2, #0x8\n"		\
		"mov w8, #64\n"			\
		"svc #0\n"			\
		"ldp x29, x30, [sp], #32\n");	\
})

int asm_write_stack(void)
{
	ASM_WRITE_HELLO_AARCH64();
	return 0;
}

int asm_write(void)
{
	int ret;
	int fd = 1;
	char msg[] = {"Hello\n"};
	size_t len = 6;

	__asm__("stp x0, x1, [sp, #-32]! \n\t"
		"mov x0, %[fd] \n\t"
		"mov x1, %[msg] \n\t"
		"mov x2, %[len] \n\t"
		"mov x8, #64 \n\t"
		"svc #0 \n\t"
		"ldp x0, x1, [sp], #32 \n\t"
		: "=g"(ret)
		: [fd] "r"(fd), [msg] "r"(msg), [len] "r"(len));

	return ret;
}

int main(void)
{
	int ret = 0;
/**
 * Test stackoverflow of asm_write()
 */
#ifdef INFINITE_LOOP
	while (1) {
#endif
		ret = asm_write();
		asm_write_stack();
#ifdef INFINITE_LOOP
	}
#endif
	printf("exit. ret = %d\n", ret);

	return 0;
}
