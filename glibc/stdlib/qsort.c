#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

int cmpstringp(const void *p1, const void *p2)
{
	return strcmp(*(const char **)p1, *(const char **)p2);
}

int cmpintp(const void *p1, const void *p2)
{
	const int i1 = *(const int *)p1;
	const int i2 = *(const int *)p2;
	return i1 - i2;
}

void test_string(void)
{
	int j;

	char *strs[] = {
		"Rong", "Tao", "Love", "Xue", "Yue", "Hua",
	};

	qsort(strs, ARRAY_SIZE(strs), sizeof(char *), cmpstringp);

	for (j = 0; j < ARRAY_SIZE(strs); j++)
		puts(strs[j]);
}

void test_int(void)
{
	int j;

	int ints[] = { 5, 2, 0, 1, 3, 1, 4};

	qsort(ints, ARRAY_SIZE(ints), sizeof(int), cmpintp);

	for (j = 0; j < ARRAY_SIZE(ints); j++)
		printf("%d\n", ints[j]);
}

int main(int argc, char *argv[])
{
	test_string();
	test_int();

	return 0;
}
