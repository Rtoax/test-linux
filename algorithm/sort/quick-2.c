/**
 *  快速排序
 *  https://rtoax.blog.csdn.net/article/details/108333441
 *
 *  不稳定
 *
 *  时间复杂度 最糟糕 O(n^2)  最好情况 O(nlogn)
 *  空间复杂度 O(logn)
 *
 *  作者：荣涛
 *  时间：2021年8月18日
 */
#include <stdio.h>

void swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

static void quick_sort_internal(int *arr, int start, int end)
{
	if(start >= end)
	return;

	/* 以第一个元素为基准 */
	int middle = arr[start];

	int left = start+1;
	int right = end;

	while (left < right) {
		while (arr[left] < middle && left < right) {
			left++;
		}
		while (arr[right] >= middle && left < right) {
			right--;
		}
		printf("(%d, %d)", left, right);
		swap(&arr[left], &arr[right]);
	}

	if (arr[start] >= arr[left]) {
		printf("(%d, %d)", start, left);
		swap(&arr[start], &arr[left]);
	}

	if (left)
		quick_sort_internal(arr, start, left - 1);

	quick_sort_internal(arr, right, end);
}

void quick_sort(int *arr, int nr)
{
	quick_sort_internal(arr, 0, nr-1);
}

int main(void)
{
	int i;
	int arr[] = {4,7,8,6,5,1,2,123,41,34,123,42,345,34,64,567,546,787,4657,456,7,456,745,67,3};

	quick_sort(arr, sizeof(arr) / sizeof(arr[0]));

	for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
		printf("%d\n", arr[i]);
	}
	return 0;
}


