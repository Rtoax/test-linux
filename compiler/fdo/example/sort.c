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

DEFINE_FN_PAD(pad1);
DEFINE_FN_PAD(pad2);
DEFINE_FN_PAD(pad3);
DEFINE_FN_PAD(pad4);
DEFINE_FN_PAD(pad5);
DEFINE_FN_PAD(pad6);
DEFINE_FN_PAD(pad7);
DEFINE_FN_PAD(pad8);
DEFINE_FN_PAD(pad9);
DEFINE_FN_PAD(pad10);
DEFINE_FN_PAD(pad11);

void
FN(sort_array)(int arr_len)
{
	printf("Bubble sorting array of %d elements\n", arr_len);
	int *data = malloc(sizeof(int) * arr_len);

	FN(rand_array)(data, arr_len);
	FN(bubble_sort)(data, arr_len);

	free(data);
}
