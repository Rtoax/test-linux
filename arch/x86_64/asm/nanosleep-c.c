#include <string.h>
#include <stdio.h>

int main(void)
{
	/**
	 * int nanosleep(const struct timespec *req, struct timespec *rem);
	 */
	__asm__("pushq $0 \n\t" /* tv_nsec = 0 */
		"pushq $1 \n\t" /* tv_sec = 1 */
		"movq %rsp, %rdi \n\t"
		"xor %rsi, %rsi \n\t" /* rem = NULL */
		"movq $35, %rax \n\t" /* __NR_nanosleep==35 */
		"syscall \n\t"
		"popq %rdi\n\t"
		"popq %rdi\n\t");

	printf("exit.\n");

	return 0;
}
