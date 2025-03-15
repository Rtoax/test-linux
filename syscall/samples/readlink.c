#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUF_LEN	1024

int main(int argc, char *argv[])
{
	int ret;
	char buffer[BUF_LEN] = { 0 };
	char *exec_file = argv[0];
	char *filename = argv[1];

	if (!filename) {
		filename = "readlink.out";
		symlink(exec_file, filename);
	}

	ret = readlink(filename, buffer, BUF_LEN);
	if (ret == -1) {
		fprintf(stderr, "readlink: %m %d:%d\n", errno, ENOENT);
		exit(1);
	}

	printf("readlink: %s\n", buffer);

	return 0;
}
