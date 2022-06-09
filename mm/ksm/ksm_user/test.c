#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char *argv[])
{
	char *buf;
	char filename[64] = "";
	struct stat stat;
	int size = 100 * 4096;
	int fd = 0;

	strcpy(filename, argv[1]);

	fd = open(filename, O_RDWR|O_CREAT, 0664);
	fstat(fd, &stat);

	buf = mmap(NULL, stat.st_size, PROT_WRITE, MAP_PRIVATE, fd, 0);
	memset(buf, 0x55, stat.st_size);

	madvise(buf, stat.st_size, MADV_MERGEABLE);

	while(1) {
		sleep(1);
	}
}

