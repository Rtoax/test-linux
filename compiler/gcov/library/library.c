#include <stdio.h>
#include <stdlib.h>

#include "library.h"

#define COMPILE_LIB
#define LIB_BRANCH_FN lib_branch_f1
#include "branch.h"
#undef LIB_BRANCH_FN

int lib_f1(void)
{
	lib_branch_f1(100000);

	return 0;
}

void bubble_sort(int *a, int n)
{
	int i, t, s = 1;
	while (s) {
		s = 0;
		for (i = 1; i < n; i++) {
			if (a[i] < a[i - 1]) {
				t = a[i];
				a[i] = a[i - 1];
				a[i - 1] = t;
				s = 1;
			}
		}
	}
}

#define ARRAY_LEN	1000

void sort_array(void)
{
	char buf[256];
	int data[ARRAY_LEN], i;


	for (i = 0; i < ARRAY_LEN; ++i) {
		data[i] = ARRAY_LEN - i;
	}
	bubble_sort(data, ARRAY_LEN);

	for (i = 0; i < ARRAY_LEN; ++i) {
		if (data[i] != i + 1) {
			fprintf(stderr, "Bubble sort failed.\n");
			exit(1);
		}
	}
}

