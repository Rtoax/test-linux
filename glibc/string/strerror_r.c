#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	char buf[256];
	strerror_r(EIO, buf, 256);
	printf("%s\n", buf);
	return 0;
}
