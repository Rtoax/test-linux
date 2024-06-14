#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(void)
{
	int fd;
	char *p;

	fd = shm_open("posix_shm", O_RDONLY, 0666);
	ftruncate(fd, 0x400000);

	p = mmap(NULL, 0x400000, PROT_READ, MAP_SHARED, fd, 0);

	printf("%c %c %c %c\n", p[0], p[1], p[2], p[3]);
	munmap(p, 0x400000);

	return 0;
}
