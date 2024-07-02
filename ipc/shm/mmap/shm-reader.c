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
	struct stat stat;
	size_t len = 0x400000;

	fd = shm_open("posix_shm", O_RDONLY, S_IWUSR | S_IWOTH);

	ftruncate(fd, len);

	fstat(fd, &stat);
	printf("stat.st_size = %ld\n", stat.st_size);

	p = mmap(NULL, len, PROT_READ, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) {
		fprintf(stderr, "mmap return NULL.\n");
		goto exit;
	}

	printf("%c %c %c %c\n", p[0], p[1], p[2], p[3]);

exit:
	munmap(p, len);
	shm_unlink("posix_shm");
	return 0;
}
