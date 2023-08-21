#include <stdio.h>
#include <ucontext.h>


ucontext_t main_ctx, ctx1;

void func(void)
{
	printf("in func\n");
}

int main(void)
{
	char stack[8192];

	getcontext(&ctx1);

	ctx1.uc_stack.ss_sp = stack;
	ctx1.uc_stack.ss_size = sizeof(stack);
	ctx1.uc_link = &main_ctx;

	makecontext(&ctx1, func, 1);

	swapcontext(&main_ctx, &ctx1);

	printf("main exit.\n");
	return 0;
}
