#include <string.h>
#include <stdio.h>

int main(void)
{
	char str[] = { "rn" };
	char s[256] = { "No.s rongtao " };

	char *ret = strpbrk(s, str);

	printf("strpbrk('%s', '%s') = '%s'\n", s, str, ret);

	return 0;
}
