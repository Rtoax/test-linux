#include <stdio.h>

/* Override -fpatchable-function-entry=N,M */
#define __patchable(N,M) __attribute__ ((patchable_function_entry (N,M)))

/**
 *    nop <------------------------------------------------
 *    nop                                        M=3
 *    nop <-----------------------------------------
 *    .type	function_patchable, @function
 * function_patchable:
 * .LFB0:
 *    .cfi_startproc                                   N=8
 *    nop
 *    nop
 *    nop
 *    nop
 *    nop <------------------------------------------------
 */
int __patchable(8,3) function_patchable_1(void)
{
	int a = 10, b = 20;
	return printf("Hello World! %d %d\n", a, b);
}

int hello(void)
{
	return printf("Hello World!\n");
}

int main(void)
{
	function_patchable_1();
	hello();
	return 0;
}
