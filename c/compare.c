#include <stdio.h>
#include <sys/types.h>

int main(void)
{
	size_t sz = 16;
	int n = -1;

	printf("%d %s %ld\n", n, n < sz ? "<" : ">=", sz);
	printf("%d %s %ld\n", n, n < (int)sz ? "<" : ">=", sz);

	return 0;
}
