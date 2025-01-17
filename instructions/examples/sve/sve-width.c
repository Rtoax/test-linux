/**
 * Get SVE width
 */
#include <stdio.h>
#include <stdint.h>
#include <arm_sve.h>


int main(void)
{
	uint64_t lanes;

	__asm__ __volatile__("CNTB %[lanes]" : [lanes]"=r"(lanes) : : );
	printf("SVE vector width is %d bytes(%d bits).\n", lanes, lanes * 8);

	lanes = svcntb();
	printf("SVE vector width is %d bytes(%d bits).\n", lanes, lanes * 8);

	return 0;
}
