#include <string.h>
#include <stdio.h>

void asm_exit(int v)
{
	__asm__("mov x0, %[v] \n\t"
		"mov w8, #0x5d \n\t"
		"svc #0x0 \n\t"
		: /* No return value */
		: [v] "r"(v));
}

int main(void)
{
	asm_exit(3);
	return 0;
}
