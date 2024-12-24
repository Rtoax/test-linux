#include <stdio.h>
#include <string.h>

int main(void)
{
	char buf1[32] = "Hello";
	char buf2[32] = "World";

	__builtin_memcpy(buf1, buf2, strlen(buf1));

	printf("buf1 %s\n", buf1);

	return 0;
}
