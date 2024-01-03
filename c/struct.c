#include <stdio.h>

struct test {
	int a;
};

struct test tests1[] = {
	{.a = 1,},
	{.a = 1,},
	{.a = 1,},
};

struct test tests2[] = {
	[0] = {.a = 1,},
	[1] = {.a = 2,},
	[2] = {.a = 3,},
	[4] = {.a = 5,},
};

struct test tests3[] = {
	[0 ... 3] = {.a = 1,},
	[4 ... 6] = {.a = 2,},
	[7] = {.a = 3,},
	[8 ... 9] = {.a = 4,},
};

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define PRINT_ARR(arr) do { \
		int i; \
		printf("------- %s ------\n", #arr); \
		for (i = 0; i < ARRAY_SIZE(arr); i++) { \
			printf("%s[%d].a = %d\n", #arr, i, arr[i].a); \
		} \
	} while (0)

int main(void)
{
	PRINT_ARR(tests1);
	PRINT_ARR(tests2);
	PRINT_ARR(tests3);
	return 0;
}
