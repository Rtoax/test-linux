#include <stdio.h>

int main(void)
{
	int a = 10, b = 20, result;

	asm (
		"ADD %[result], %[a], %[b]"
		: [result] "=r" (result)
		: [a] "r" (a),
		  [b] "r" (b)
	);

	printf("The result is: %d\n", result);
	return 0;
}
