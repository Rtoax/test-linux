#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>


void asm_exit(int v)
{
	int ret;
	__asm__("mov %1, %%edi \n\t"
		"movq $60, %%rax \n\t"
		"syscall \n\t"
		: "=r"(ret)
		: "r"(v));
}

int main(void)
{
	asm_exit(0xff);
	printf("exit.\n");
	return 0;
}
