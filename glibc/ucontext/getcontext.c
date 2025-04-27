#include <stdio.h>
#include <ucontext.h>
#include <unistd.h>

int main(void)
{
	ucontext_t uctx;
	stack_t *stack;

	getcontext(&uctx);

	stack = &uctx.uc_stack;

	printf("stack->ss_flags = %x\n", stack->ss_flags);
	printf("stack->ss_size = %ld\n", stack->ss_size);

#ifdef TEST_SETCONTEXT
	sleep(1);
	setcontext(&uctx);
#endif

	return 0;
}
