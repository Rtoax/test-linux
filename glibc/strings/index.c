#include <stdio.h>
#include <strings.h>

int main(void)
{
	char str[] = {"Hello Wrold1, Hello World2"};
	char ch = 'd';

	printf("index = %s\n", index(str, ch));
	printf("rindex = %s\n", rindex(str, ch));

	return 0;
}
