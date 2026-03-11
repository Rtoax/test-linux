#include <stdio.h>

int main(void)
{
	asm volatile ("paciasp");
	return 0;
}
