#include <stdio.h>
#include <string.h>

int main(void)
{
	int a = 1;
	char s[64] = {0};
	int b = 2;

	strncpy(s, "hello", sizeof(s));

	printf("a = %d\n", a);
	printf("s = %s\n", s);
	printf("b = %d\n", b);

	return 0;
}
