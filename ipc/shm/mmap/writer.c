#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(void)
{
	char *p;
	int fd;
	struct stat stat;
	size_t len = 0x400000;

	fd = shm_open("posix_shm", O_CREAT | O_RDWR, 0666);
	ftruncate(fd, len);

	fstat(fd, &stat);
	printf("stat.st_size = %ld\n", stat.st_size);

	p = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	memset(p, 'A', len);
	munmap(p, len);

	return 0;
}
