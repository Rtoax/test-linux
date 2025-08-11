#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>


int main(void)
{
	unsigned long cr3;

	asm ("movq %%cr3, %0\n" : "=r"(cr3));
	printf("cr3 = %lx\n", cr3);

	/**
	 * User-mode modification of CR3 will trigger X86_TRAP_GP
	 */
	cr3 |= 0x1000;
	asm volatile("mov %0, %%cr3" :: "r"(cr3));

	return 0;
}
