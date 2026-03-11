#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>


void asm_out(void)
{
	__asm__(
		"mov $0x3f8, %dx\n"
		"mov $'r', %al\n"
		"out %al, (%dx)\n"
		"mov $'t', %al\n"
		"out %al, (%dx)\n"
		"mov $'\n', %al\n"
		"out %al, (%dx)\n"
		"hlt\n"
	);
}

int main(void)
{
	asm_out();
	printf("exit.\n");
	return 0;
}
