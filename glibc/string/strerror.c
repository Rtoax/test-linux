#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	printf("%d\n", errno);
	printf("%d:%s\n", errno, strerror(errno));
	printf("%d:%s\n", EPERM, strerror(EPERM));
	printf("%d:%s\n", EAGAIN, strerror(EAGAIN));
	return 0;
}
