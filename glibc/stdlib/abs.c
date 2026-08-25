#include <stdio.h>
#include <stdlib.h>

int main(void)
{
#define ABS(v) printf("abs(%s) = %d\n", #v, abs(v));
#define LABS(v) printf("labs(%s) = %ld\n", #v, labs(v));
#define LLABS(v) printf("llabs(%s) = %lld\n", #v, llabs(v));
	ABS(1);
	ABS(-1);
	ABS(0);
	ABS(1 - 99);
	LABS(1);
	LLABS(1);
	return 0;
}
