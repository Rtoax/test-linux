#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	int ret;
	char *file = "rongtao.out";

	ret = mkdir(file, 0777);
	printf("mkdir ret: %d\n", ret);

	ret = chown(file, 0, 0);
	if (ret == -1) {
		fprintf(stderr, "chown %m\n");
		return -errno;
	}
	return 0;
}
