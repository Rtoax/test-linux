#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "library.h"

#define COMPILE_LIB
#define LIB_BRANCH_FN lib_branch_f1
#include "branch.h"
#undef LIB_BRANCH_FN
#undef COMPILE_LIB

int lib_f1(void)
{
	unsigned long ret;

	srand((int)time(0));

	ret = lib_branch_f1(rand() % 100000000);

	return 0;
}

#define LAYOUT_FN_TEST	lib_layout_test
#define LAYOUT_FN_A		lib_layout_A
#define LAYOUT_FN_B		lib_layout_B
#define LAYOUT_FN_C		lib_layout_C
#define LAYOUT_FN_D		lib_layout_D
#include "layout.h"
#undef LAYOUT_FN_TEST
#undef LAYOUT_FN_A
#undef LAYOUT_FN_B
#undef LAYOUT_FN_C
#undef LAYOUT_FN_D


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

