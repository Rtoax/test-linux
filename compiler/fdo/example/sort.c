/**
 * ref: https://gcc.gnu.org/wiki/AutoFDO/Tutorial
 */
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "sort.h"


void
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

void
FN(pad1)(int *arr, int arr_len) { return; }
void
FN(pad2)(int *arr, int arr_len) { return; }
void
FN(pad3)(int *arr, int arr_len) { return; }
void
FN(pad4)(int *arr, int arr_len) { return; }

void
FN(rand_array)(int *arr, int arr_len)
{
	int i;

	for (i = 0; i < arr_len; ++i) {
		arr[i] = rand();
	}
}

void
FN(sort_array)(int arr_len)
{
	printf("Bubble sorting array of %d elements\n", arr_len);
	int *data = malloc(sizeof(int) * arr_len);

	FN(rand_array)(data, arr_len);
	FN(bubble_sort)(data, arr_len);

	free(data);
}
