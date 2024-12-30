#include <stdio.h>
#include <string.h>

int main(void)
{
	char buf1[32] = "Hello";
	char buf2[32] = "World";

	int len = __builtin_strlen(buf1);
	__builtin_memcpy(buf1, buf2, len);

	if (__builtin_strcmp(buf1, buf2)) {
		fprintf(stderr, "__builtin_memcpy failed.\n");
		return -1;
	}

	printf("buf1 %s\n", buf1);

	return 0;
}
