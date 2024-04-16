#include <stdio.h>

typedef struct test_struct {
	int id;
} ts_t;

ts_t tss[123];

#pragma GCC poison tss
#pragma GCC poison printf

int main(void)
{
#ifdef ERROR
	tss[1].id = 1;
	printf("Hello\n");
#endif
	return 0;
}
