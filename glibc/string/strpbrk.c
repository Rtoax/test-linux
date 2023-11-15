#include <string.h>
#include <stdio.h>

int main(void)
{
	char str[] = {"n"}, s[256] = {"No.s rongtao "};

	char *ret = strpbrk(s, str);

	printf("%s\n%s\n%s\n",ret, str,s);

	return 0;
}
