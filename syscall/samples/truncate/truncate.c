#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

#include "syscall_helpers.h"


int main(int argc, char *argv[])
{
	int ret;
	size_t len, blk;
	struct stat statbuf;
	const char *file = "tmp.dat";


	len = 1024 * 1024 * 10;

	create_file(file, 'a', len);

	stat(file, &statbuf);
	blk = statbuf.st_blksize * statbuf.st_blocks;
	printf("size %ld (created %ld, end %ld, blk %ld)\n", statbuf.st_size,
		len, file_seek_end(file), blk);

	ret = truncate(file, len / 2);
	if (ret == -1) {
		fprintf(stderr, "truncate %m\n");
		return -errno;
	}

	stat(file, &statbuf);
	blk = statbuf.st_blksize * statbuf.st_blocks;
	printf("size %ld (truncate %ld, end %ld, blk %ld)\n", statbuf.st_size,
		len / 2, file_seek_end(file), blk);

	truncate(file, len * 2);

	stat(file, &statbuf);
	blk = statbuf.st_blksize * statbuf.st_blocks;
	printf("size %ld (truncate %ld, end %ld, blk %ld)\n", statbuf.st_size,
		len * 2, file_seek_end(file), blk);

	return 0;
}
