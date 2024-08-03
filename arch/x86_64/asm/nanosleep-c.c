#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>


int asm_sleep1(void)
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

	return 0;
}

int asm_sleep2(int sec)
{
	int ret = -EINVAL;

	struct timespec ts = {sec, 0};

	__asm__("movq %1, %%rdi \n\t"  /* rdi = &ts */
		"xor %%rsi, %%rsi \n\t" /* rem = NULL */
		"movq $35, %%rax \n\t" /* __NR_nanosleep==35 */
		"syscall \n\t"
		: "=r"(ret)
		: "r"(&ts));

	if (ret) {
		fprintf(stderr, "nanosleep failed %d, sec = %d, %s\n",
			ret, sec, strerror(-ret));
	}

	return ret;
}

int main(void)
{
	asm_sleep1();
	asm_sleep2(1);
	asm_sleep2(-1);
	printf("exit.\n");

	return 0;
}
