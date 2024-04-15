#include <stdio.h>
#include <string.h>
#include <sys/types.h>

char *strcaseswap(char *str, ssize_t len)
{
	char *c = str;
	while (*c) {
		*c = (*c)&0xdf;
		c++;
	}
	return str;
}

#ifdef TEST
int main(void)
{
	char str[] = {"AbasdADDadLJ"};
	printf("%s->%s\n", str, strcaseswap(str, strlen(str)));
}
#endif
