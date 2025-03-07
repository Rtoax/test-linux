/**
 * ref: https://gcc.gnu.org/wiki/AutoFDO/Tutorial
 */
#include <stdio.h>
#include <stdlib.h>

#include "common.h"


void bubble_sort(int *a, int n)
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

void sort_array(int arr_len)
{
	printf("Bubble sorting array of %d elements\n", arr_len);
	int *data = malloc(sizeof(int) * arr_len);

	rand_array(data, arr_len);
	bubble_sort(data, arr_len);

	free(data);
}

int main(void)
{
	start();
	sort_array(30000);
	stop();
	return 0;
}

