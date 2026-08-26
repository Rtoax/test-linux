#include <stdio.h>

int i = 0x3f; /* .data */
static int big_arr1[4096 * 4096] = { 1 }; /* .data */
int big_arr2[4096 * 4096] = { 1 }; /* .data */

int main(void)
{
	(void)big_arr1;
	return 0;
}
