#include <string.h>
#include <stdio.h>
#include <time.h>

int main(void)
{
	/**
	 * int nanosleep(const struct timespec *req, struct timespec *rem);
	 */
	__asm__("pushq %rax \n\t"
		"pushq %rdi \n\t"
		"pushq %rsi \n\t"
		"pushq $0 \n\t" /* tv_nsec = 0 */
		"pushq $1 \n\t" /* tv_sec = 1 */
		"movq %rsp, %rdi \n\t"
		"xor %rsi, %rsi \n\t" /* rem = NULL */
		"movq $35, %rax \n\t" /* __NR_nanosleep==35 */
		"syscall \n\t"
		"popq %rdi\n\t"
		"popq %rdi\n\t"
		"popq %rsi\n\t"
		"popq %rdi\n\t"
		"popq %rax\n\t");

#if 0
	struct timespec ts = {1, 0};

	__asm__("movq %0, %rdi \n\t"  /* rdi = &ts */
		"xor %rsi, %rsi \n\t" /* rem = NULL */
		"movq $35, %rax \n\t" /* __NR_nanosleep==35 */
		"syscall \n\t"
		: /* No return */
		: "r"(&ts));
#endif

	printf("exit.\n");

	return 0;
}
