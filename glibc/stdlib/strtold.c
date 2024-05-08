#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *buf;

	printf("%Lf\n", strtold("123.34asdf", &buf));
	printf("%s\n", buf);

	return 0;
}
