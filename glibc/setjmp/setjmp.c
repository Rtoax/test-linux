#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>

jmp_buf main_loop;

void abort_to_main_loop(int status)
{
	printf("%s:%d\n", __func__, status);
	longjmp(main_loop, status);
}

void do_command(void)
{
	printf("%s\n", __func__);
	abort_to_main_loop(1);
}

int main(void)
{
	if (setjmp(main_loop))
		puts("Back at main loop....");
	else
		do_command();
	return 0;
}

