#include <stdio.h>

int main(void)
{
	long array[] = {1, 2, 3, 4, 5};
	long length = sizeof(array) / sizeof(array[0]);
	long sum = 0;

	asm (
		"MOV x1, #0\n"
		"MOV x2, #0\n"
	"loop:\n"
		"LDR x0, [%[array], x2, LSL #3]\n"
		"ADD x1, x1, x0\n"
		"ADD x2, x2, #1\n"
		"CMP x2, %[length]\n"
		"BLT loop\n"
		: [sum] "=r"(sum)
		: [array] "r"(array),
		  [length] "r"(length)
		: "x0", "x1", "x2", "cc"
	);

	printf("The sum of the array is: %ld, len = %ld\n", sum, length);
	return 0;
}
