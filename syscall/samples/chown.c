#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>		/*S_IRUSR */

int main(int argc, char *argv[])
{
	int ret;
	char *file = argv[1];

	ret = chown(file, 0, 0);
	if (ret == -1) {
		fprintf(stderr, "chown %m\n");
		return -errno;
	}
	return 0;
}
