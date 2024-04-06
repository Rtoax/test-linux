#include <stdio.h>
#include <malloc.h>

int min(int x, int y)
{
	return x < y ? x : y;
}

void merge_sort(int arr[], int len)
{
	int *a = arr;
	int *b = (int *) malloc(len * sizeof(int));
	int seg, start;
	for (seg = 1; seg < len; seg += seg) {
		for (start = 0; start < len; start += seg * 2) {
			int low = start;
			int mid = min(start + seg, len);
			int high = min(start + seg * 2, len);
			int k = low;
			int start1 = low, end1 = mid;
			int start2 = mid, end2 = high;
			while (start1 < end1 && start2 < end2)
				b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
			while (start1 < end1)
				b[k++] = a[start1++];
			while (start2 < end2)
				b[k++] = a[start2++];
		}
		int *temp = a;
		a = b;
		b = temp;
	}
	if (a != arr) {
		int i;
		for (i = 0; i < len; i++)
			b[i] = a[i];
		b = a;
	}
	free(b);
}

int main(void)
{
	int i;
	int arr[] = {1,4,1,1,1,12,3,123,12,37,8,3,6,9};
	int len = sizeof(arr)/sizeof(arr[0]);
	merge_sort(arr, len);

	for (i = 0; i < len; i++)
		printf("%d%c", arr[i], i == len - 1 ? '\n' : ' ');

	return 0;
}
