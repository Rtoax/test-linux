#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *buf;
	char filename[64] = "";
	struct stat stat;
	int i, fd;
	int pagesize = getpagesize();

	if (argc < 2) {
		fprintf(stderr, "Must specfiy a file\n");
		exit(1);
	}

	strcpy(filename, argv[1]);

	fd = open(filename, O_RDWR | O_CREAT, 0664);
	fstat(fd, &stat);

	buf = mmap(NULL, stat.st_size, PROT_WRITE, MAP_PRIVATE, fd, 0);
	memset(buf, 0x55, stat.st_size);

	madvise(buf, stat.st_size, MADV_MERGEABLE);

	for (i = 0; i < stat.st_size; i += pagesize) {
		char __attribute__((unused)) ch = buf[i];
	}

	return 0;
}
