/**
 * R_AARCH64_ADR_PREL_PG_HI21
 */
#include <stdio.h>
#include <stdint.h>

int8_t gi8 = 0;	/* .bss, GLOBAL */

int main(void)
{
	gi8 = 10;
	return 0;
}
