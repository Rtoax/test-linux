/**
 * ref: https://gcc.gnu.org/wiki/AutoFDO/Tutorial
 */
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

#define ARRAY_LEN 30000

void __cacheline_align
bubble_sort(int *a, int n)
{
	int i, s = 1;
	while (s) {
		s = 0;
		for (i = 1; i < n; i++) {
			if (a[i] < a[i - 1]) {
				swap_int(&a[i], &a[i - 1]);
				s = 1;
			}
		}
	}
}

void __cacheline_align
sort_array(void)
{
	printf("Bubble sorting array of %d elements\n", ARRAY_LEN);
	int data[ARRAY_LEN], i;

	for (i = 0; i < ARRAY_LEN; ++i) {
		data[i] = rand();
	}
	bubble_sort(data, ARRAY_LEN);
}

int main()
{
	start();
	sort_array();
	stop();

	return 0;
}

