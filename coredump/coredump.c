#include <stdio.h>

int overflow(void)
{
	char *s = NULL;
	char c = s[1024];
	return c;
}

int main(void)
{
	overflow();
	return 0;
}
