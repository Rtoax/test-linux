#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

int cmpstringp(const void *p1, const void *p2)
{
	return strcmp(*(const char **)p1, *(const char **)p2);
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

int main(int argc, char *argv[])
{
	test_string();

	return 0;
}

