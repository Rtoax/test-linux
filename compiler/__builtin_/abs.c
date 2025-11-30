#include <stdio.h>

int main(int argc, char *argv[])
{
	printf("abs %d\n", __builtin_abs(-1));
	printf("labs %ld\n", __builtin_labs(-1LL));
	printf("llabs %lld\n", __builtin_llabs(-1LL));
	return 0;
}
