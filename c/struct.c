#include <stdio.h>

#define __unused __attribute__((unused))

struct test {
	int a;
};

struct test test1 = {
	a: 1,
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

int widths[] = { [0 ... 3] = 1, [5 ... 9] = 2, [10] = 3 };

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define PR_S(s) printf("%s.a = %d\n", #s, s.a)
#define PR_S_ARR(arr) do { \
		int i; \
		printf("------- %s ------\n", #arr); \
		for (i = 0; i < ARRAY_SIZE(arr); i++) { \
			printf("%s[%d].a = %d\n", #arr, i, arr[i].a); \
		} \
	} while (0)
#define PR_ARR(arr) do { \
		int i; \
		printf("------- %s ------\n", #arr); \
		for (i = 0; i < ARRAY_SIZE(arr); i++) { \
			printf("%s[%d] = %d\n", #arr, i, arr[i]); \
		} \
	} while (0)

int main(void)
{
	struct test __unused t1 = { .a = 0 };
	struct test __unused t2 = { 0 };
#if !defined(__clang__)
	/* clang not support a : 10 */
	struct test __unused t3 = { a : 10 };
#endif
	PR_S(test1);
	PR_S_ARR(tests1);
	PR_S_ARR(tests2);
	PR_S_ARR(tests3);
	PR_ARR(widths);
	return 0;
}
