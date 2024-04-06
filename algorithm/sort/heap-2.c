/**
 * 堆排序
 */
#include <stdio.h>

void swap(int *a, int *b)
{
	int temp = *b;
	*b = *a;
	*a = temp;
}

/* 小顶堆 */
#if 0

void heapify(int tree[], int n, int i)
{
	if (i >= n)
		return;

	int c1 = 2 * i + 1; //左孩子
	int c2 = 2 * i + 2; //右孩子

	/* 假定父节点是最大值 */
	int min = i; //

	/* 如果左孩子大于父节点，标记max */
	if(c1 < n && tree[c1] < tree[min]) {
		min = c1;
	}
	/* 如果右孩子大于父节点，标记max */
	if(c2 < n && tree[c2] < tree[min]) {
		min = c2;
	}

	if(min != i) {
		/* 最大值交换至父节点 */
		swap(&tree[min], &tree[i]);
		heapify(tree, n, min);
	}
}
/* 大顶堆heapify */
#else
void heapify(int tree[], int n, int i)
{
	if(i>=n)
		return;

	int c1 = 2*i + 1; //左孩子
	int c2 = 2*i + 2; //右孩子

	/* 假定父节点是最大值 */
	int max = i;

	/* 如果左孩子大于父节点，标记max */
	if(c1 < n && tree[c1] > tree[max]) {
		max = c1;
	}
	/* 如果右孩子大于父节点，标记max */
	if(c2 < n && tree[c2] > tree[max]) {
		max = c2;
	}

	if(max != i) {
		/* 最大值交换至父节点 */
		swap(&tree[max], &tree[i]);
		heapify(tree, n, max);
	}
}
#endif

void build_heap(int tree[], int n)
{
	/* 最后一个节点 */
	int last_node = n - 1;
	/* 他的父节点 */
	int parent = (last_node - 1) / 2;
	int i;

	/* 从最后一个非叶子节点开始遍历，进行heapify */
	for(i=parent; i >= 0; i--) {
		heapify(tree, n, i);
	}
}

void heap_sort(int tree[], int n)
{
	/* 构建一个堆 */
	build_heap(tree, n);

	int i;
	for(i = n - 1; i >= 0; i--) {
		/* 取出最后一个节点，与根交换，最大值跑到最后一个节点上去了 */
		swap(&tree[i], &tree[0]);

		/* 跳过最后一个节点，继续进行heapify */
		heapify(tree, i, 0);
	}
}

int main(void)
{
	int tree[] = {2, 5, 3, 1, 10, 4, 123, 12, 3, 12, 31, 23, 12, 4, 23, 54234,
			5, 234, 52, 45, 13, 4132};

	int i, size = sizeof(tree)/sizeof(tree[0]);

	heap_sort(tree, size);

	for (i = 0; i < size; i++) {
		printf("%d%c", tree[i], i == size -1 ? '\n': ' ');
	}

	return 0;
}
