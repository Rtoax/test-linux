#include <stdio.h>
#include "../attribute/patchable_function_entry.h"
#include "../attribute/hotpatch.h"

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
int __patchable(8, 3) function_patchable_1(void)
{
	int a = 10, b = 20;
	return printf("Hello World! %d %d\n", a, b);
}

#ifdef __s390__ /* see linux:scripts/recordmcount.pl CC_USING_HOTPATCH */
int function_hotpatch_1(void) __hotpatch(8, 3);
int function_hotpatch_1(void)
{
	int a = 30, b = 40;
	return printf("Hello World! %d %d\n", a, b);
}
#else
#define function_hotpatch_1()
#endif

int hello(void)
{
	return printf("Hello World!\n");
}

int main(void)
{
	function_patchable_1();
	function_hotpatch_1();
	hello();
	return 0;
}
