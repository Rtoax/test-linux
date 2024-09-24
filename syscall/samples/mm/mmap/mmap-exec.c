#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <wait.h>
#include <errno.h>


static int static_asm_putchar(int c)
{
#if defined(__x86_64__)
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
#elif defined(__aarch64__)
# if 0 /* FIXME: Print nothing?! */
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
# endif
# define ASM_WRITE_HELLO_AARCH64() ({		\
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
	ASM_WRITE_HELLO_AARCH64();
#endif
	return 0xdead;
}

static int static_asm_putchar_end(int c)
{
	return 0;
}

typedef int (*fn_putchar)(int c);

int main(void)
{
	int ret;
	unsigned long map_len, addr;
	void *mem;
	fn_putchar fn;

	map_len = static_asm_putchar_end - static_asm_putchar;

	/* This is PIE ELF */
	if ((unsigned long)main >= 0x5000000) {
		addr = 0;
	} else {
		addr = 0x500000;
	}

	/**
	 * PROT_EXEC is not necessary here if mprotect(2) pass PROT_EXEC.
	 */
	mem = mmap((void *)addr, map_len, PROT_READ | PROT_WRITE | PROT_EXEC,
		   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (mem == MAP_FAILED) {
		fprintf(stderr, "remote mmap failed.\n");
		goto close_ret;
	}

	memcpy(mem, static_asm_putchar, map_len);
	mprotect(mem, map_len, PROT_READ | PROT_EXEC);

	printf("main = %p\n", main);
	printf("addr = 0x%lx\n", addr);
	printf("mem = %p\n", mem);

	fn = (fn_putchar)mem;

	ret = fn('a');
	if (ret != 0xdead) {
		fprintf(stderr, "Failed\n");
		abort();
	}
	printf("ret = %x\n", ret);

close_ret:
	munmap(mem, map_len);
	return 0;
}
