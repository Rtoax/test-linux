#include <ucontext.h>
#include <stdio.h>


int main(void)
{
	ucontext_t u;
	stack_t *stack;


	getcontext(&u);
	stack = &u.uc_stack;

	printf("stack->ss_flags = %x\n", stack->ss_flags);
	printf("stack->ss_size = %ld\n", stack->ss_size);

	return 0;
}
