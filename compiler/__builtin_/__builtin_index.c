#include <stdio.h>
#include <strings.h>

int main(void)
{
	char str[] = {"Hello Wrold1, Hello World2"};
	char ch = 'd';

	printf("__builtin_index = %s\n", __builtin_index(str, ch));
	printf("index = %s\n", index(str, ch));

	return 0;
}