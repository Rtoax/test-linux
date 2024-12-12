#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>

sigjmp_buf main_loop;

void abort_to_main_loop(int status)
{
	printf("%s:%d\n", __func__, status);
	siglongjmp(main_loop, status);
}

void do_command(void)
{
	printf("%s\n", __func__);
	abort_to_main_loop(1);
}

int main(void)
{
	if (sigsetjmp(main_loop, 1))
		puts("Back at main loop....");
	else
		do_command();

	return 0;
}

