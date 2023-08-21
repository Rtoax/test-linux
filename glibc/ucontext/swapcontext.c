#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>


static ucontext_t uctx_main, uctx1, uctx2;

#define handle_error(msg) do { \
		perror(msg); \
		exit(EXIT_FAILURE); \
	} while (0)

static void func1(void)
{
	printf("func1: started\n");
	if (swapcontext(&uctx1, &uctx2) == -1)
		handle_error("swapcontext");
	printf("func1: returning\n");
}

static void func2(void)
{
	printf("func2: started\n");
	if (swapcontext(&uctx2, &uctx1) == -1)
		handle_error("swapcontext");
	printf("func2: returning\n");
}

int main(int argc, char *argv[])
{
	char func1_stack[8192];
	char func2_stack[8192];

	if (getcontext(&uctx1) == -1)
		handle_error("getcontext");
	uctx1.uc_stack.ss_sp = func1_stack;
	uctx1.uc_stack.ss_size = sizeof(func1_stack);
	uctx1.uc_link = &uctx_main;
	makecontext(&uctx1, func1, 0);

	if (getcontext(&uctx2) == -1)
		handle_error("getcontext");
	uctx2.uc_stack.ss_sp = func2_stack;
	uctx2.uc_stack.ss_size = sizeof(func2_stack);
	uctx2.uc_link = &uctx1;
	makecontext(&uctx2, func2, 0);

	if (swapcontext(&uctx_main, &uctx2) == -1)
		handle_error("swapcontext");

	printf("main: exiting\n");
	exit(EXIT_SUCCESS);
}
