#include <string.h>
#include <stdio.h>

int main(void)
{
	char *str = "hello world\n";
	long len = strlen(str);

	int ret = 0;

	/* write(2, str, len); */
	__asm__("movq $1, %%rax \n\t"
		"movq $2, %%rdi \n\t"
		"movq %1, %%rsi \n\t"
		"movl %2, %%edx \n\t"
		"syscall"
		: "=g"(ret)
		: "g"(str), "g" (len));

	/* exit(0); */
	__asm__("movq $60, %%rax \n\t" /* NR_exit = 60 */
		"movq %1, %%rdi \n\t"  /* exit(rdi) */
		"syscall"
		: "=g"(ret) /* return */
		: "g"(0) /* %1 = 0, exit(%1) */);

	return 0;
}
