#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	int ret;
	char *file = argv[1];

	/* root uid == 0 */
	ret = fchownat(AT_FDCWD, file, 0, 0, 0);
	if (ret == -1) {
		fprintf(stderr, "fchownat %m\n");
		return -errno;
	}
	return 0;
}
