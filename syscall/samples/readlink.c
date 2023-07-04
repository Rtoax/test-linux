#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUF_LEN	1024

int main(void)
{
	int ret;
	char buffer[BUF_LEN] = {0};

	ret = readlink("/etc/os-release", buffer, BUF_LEN);
	if (ret > 0)
		printf("readlink: %s\n", buffer);
	else
		fprintf(stderr, "readlink: %s\n", strerror(errno));

	return 0;
}
