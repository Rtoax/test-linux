/**
 *  插入排序
 *  https://rtoax.blog.csdn.net/article/details/108333441
 *
 *  稳定
 *
 *  时间复杂度 O(n^2)
 *  空间复杂度 O(1)
 *
 *  作者：荣涛
 */
#include <stdio.h>

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void insert_sort(int *arr, int nr)
{
	int i, j;

	for (i = 1; i < nr; i++) {
		int min_idx = i;
		for (j = min_idx - 1; j >= 0; j--) {
			if(arr[min_idx] < arr[j]) {
				swap(&arr[min_idx], &arr[j]);
				min_idx = j;
			}
		}
	}
}

/**
 * https://rtoax.blog.csdn.net/article/details/108333441
 */
void insertion_sort(int arr[],  int len)
{
	int i, j, key;
	for (i = 1; i < len; i++){
		key = arr[i];
		j = i - 1;
		while ((j >= 0) && (arr[j] > key)) {
				arr[j + 1] = arr[j];
				j--;
		}
		arr[j+1] = key;
	}
}

int main(void)
{
	int i;
	int arr[] = {4, 3, 2, 5, 6, 7, 8, 123, 12, 3, 12, 345, 234, 534, 56, 4, 342, 46, 3456, 354, 6};

	insert_sort(arr,  sizeof(arr)/sizeof(arr[0]));

	for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
		printf("%d\n", arr[i]);
	}

	return 0;
}


