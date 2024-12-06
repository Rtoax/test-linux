/**
 * Ternary conditional operator (if a then b else c or a ? b : c)
 */
#include <stdio.h>

int main(void)
{
#define PR(expr)	printf("%-64s : %d\n", #expr, expr);
	PR(10 < 20 ?: 30);
	return 0;
}
