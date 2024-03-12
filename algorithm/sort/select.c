/**
 *  选择排序
 *
 *  不稳定
 *
 *  时间复杂度 O(n^2)
 *  空间复杂度 O(1)
 *
 *  作者：荣涛
 *  时间：2021年8月18日10:56:47
 */
#include <stdio.h>

void swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
	//printf("swap %d-%d\n", *a, *b);
}

void select_sort(int *arr, int nr)
{
	int i, j;

	for (i = 0; i < nr - 1; i++) {
		int min_idx = i;

		for (j = i + 1; j < nr; j++) {
			if (arr[min_idx] > arr[j]) {
				min_idx = j;
			}
		}
		if (i != min_idx)
			swap(&arr[i], &arr[min_idx]);
	}
}

int main(void)
{
	int i;
	int arr[] = {4, 3, 2, 5, 6, 7, 8, 123, 12, 3, 12, 345, 234, 534, 56, 4,
		     342, 46, 3456, 354, 6};

	select_sort(arr, sizeof(arr) / sizeof(arr[0]));

	for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
		printf("%d\n", arr[i]);
	}
	return 0;
}

