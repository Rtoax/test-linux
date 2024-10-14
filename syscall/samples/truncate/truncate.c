#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

#include "helpers.h"


int main(int argc, char *argv[])
{
	int ret;
	size_t len;
	struct stat statbuf;
	const char *file = "tmp.dat";


	len = 1024 * 1024 * 10;

	create_file(file, 'a', len);

	stat(file, &statbuf);
	printf("size %ld (created %ld, end %ld)\n", statbuf.st_size, len,
		file_seek_end(file));

	ret = truncate(file, len / 2);
	if (ret == -1) {
		fprintf(stderr, "truncate %m\n");
		return -errno;
	}

	stat(file, &statbuf);
	printf("size %ld (truncate %ld, end %ld)\n", statbuf.st_size, len / 2,
		file_seek_end(file));

	truncate(file, len * 2);

	stat(file, &statbuf);
	printf("size %ld (truncate %ld, end %ld)\n", statbuf.st_size, len * 2,
		file_seek_end(file));

	return 0;
}
