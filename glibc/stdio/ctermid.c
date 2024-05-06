#include <stdio.h>

int main(void)
{
	char str[256];

	printf("ctermid: %s\n", ctermid(str));

	printf("str: %s\n", str);

	return 0;
}
