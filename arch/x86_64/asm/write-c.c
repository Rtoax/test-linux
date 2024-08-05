#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>


void asm_write(void)
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
		: [fd]"r"(fd), [msg]"r"(msg), [len]"r"(len));
}

int main(void)
{
	asm_write();
	printf("exit.\n");
	return 0;
}
