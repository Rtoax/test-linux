#include <stdio.h>
#include <strings.h>

int main(void)
{
	char str[] = {"Hello World1, Hello World2"};
	char ch = 'd';

	printf("__builtin_index = %s\n", __builtin_index(str, ch));
	printf("__builtin_rindex = %s\n", __builtin_rindex(str, ch));

	return 0;
}