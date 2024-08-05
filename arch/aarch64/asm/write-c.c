#include <string.h>
#include <stdio.h>

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
	asm_write();
	printf("exit.\n");

	return 0;
}
