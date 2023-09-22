/**
 * Description: Get Current Exception Level in userspace
 *
 * 2023-09-22	Rong Tao	Create this.
 */
#include <stdio.h>
#include <stdint.h>
#include "currentel.h"


int main(void)
{
	/**
	 * CurrentEL however is not readable from EL0 as shown on the
	 * ARMv8 manual C5.2.1 "CurrentEL, Current Exception Level"
	 * section "Accessibility". Trying to run it in Linux userland
	 * raises SIGILL.
	 */
	register int el = currentel();
	printf("EL = %d\n", el);
	return 0;
}
