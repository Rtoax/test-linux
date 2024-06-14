#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(void)
{
	char *p;
	int fd;

	fd = shm_open("posix_shm", O_CREAT | O_RDWR, 0666);
	ftruncate(fd, 0x400000);

	p = mmap(NULL, 0x400000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	memset(p, 'A', 0x400000);
	munmap(p, 0x400000);

	return 0;
}
