#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUF_LEN	1024

int main(int argc, char *argv[])
{
	int ret;
	char buffer[BUF_LEN] = {0};
	char *filename = argv[0];


	symlink(filename, "readlink.out");

	ret = readlink("readlink.out", buffer, BUF_LEN);
	if (ret > 0)
		printf("readlink: %s\n", buffer);
	else
		fprintf(stderr, "readlink: %s\n", strerror(errno));

	return 0;
}
