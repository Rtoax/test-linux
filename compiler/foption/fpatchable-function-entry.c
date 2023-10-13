#include <stdio.h>

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
int __patchable(8,3) function_patchable(void)
{
	int a = 10, b = 20;
	return printf("Hello World! %d %d\n", a, b);
}

int main(void)
{
	function_patchable();
	return 0;
}
