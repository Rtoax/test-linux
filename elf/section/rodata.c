#include <stdio.h>

const int i = 0x3f; /* .data */
const static int big_arr1[4096 * 4096] = { 1 }; /* .data */
const int big_arr2[4096 * 4096] = { 1 }; /* .data */

int main(void)
{
	(void)big_arr1;
	return 0;
}
