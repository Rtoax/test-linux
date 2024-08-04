#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>


void asm_write(void)
{
	int ret;
	char msg[] = {"Hello\0"};
	size_t len = 6;

	__asm__("mov $1, %%edi \n\t"
		"movq %1, %%rsi \n\t"
		"movq %2, %%rdx \n\t"
		"movq $1, %%rax \n\t"
		"syscall \n\t"
		: "=r"(ret)
		: "r"(msg), "r"(len));
}

int main(void)
{
	asm_write();
	printf("exit.\n");
	return 0;
}
