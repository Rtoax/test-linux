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
