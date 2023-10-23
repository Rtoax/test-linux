/*
 * callmaxofthree.c
 *
 * Illustrates how to call the maxofthree function we wrote in assembly
 * language.
 */

#include <stdio.h>

int maxofthree(int, int, int);

int main(void)
{
	printf("%d\n", maxofthree(1, -4, -7));
	printf("%d\n", maxofthree(2, -6, 1));
	printf("%d\n", maxofthree(2, 3, 1));
	printf("%d\n", maxofthree(-2, 4, 3));
	printf("%d\n", maxofthree(2, -6, 5));
	printf("%d\n", maxofthree(2, 4, 6));
	return 0;
}

