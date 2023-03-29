/**
 * ref: https://gcc.gnu.org/wiki/AutoFDO/Tutorial
 */
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "sort.h"


void __cacheline_align __noinline
FN(bubble_sort)(int *a, int n)
{
	int i, s = 1;
	while (s) {
		s = 0;
		for (i = 1; i < n; i++) {
			if (a[i] < a[i - 1]) {
				FN(swap_int)(&a[i], &a[i - 1]);
				s = 1;
			}
		}
	}
}

void __cacheline_align __noinline
FN(sort_array)(int arr_len)
{
	printf("Bubble sorting array of %d elements\n", arr_len);
	int *data = malloc(sizeof(int) * arr_len);
	int i;

	for (i = 0; i < arr_len; ++i) {
		data[i] = rand();
	}
	FN(bubble_sort)(data, arr_len);

	free(data);
}
