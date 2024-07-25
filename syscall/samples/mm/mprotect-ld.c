#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FILE_TO_MAP "/dev/zero"

void print_maps(void)
{
	char cmd[128];
	printf("-----------------------------------------\n");
	snprintf(cmd, sizeof(cmd) - 1, "cat /proc/%d/maps | grep "FILE_TO_MAP,
		 getpid());
	system(cmd);
}

int main(void)
{
	int fd;
	int pgsz, size;
	char *mem;

	pgsz = getpagesize();
	size = pgsz * 10;
	printf("size = %d\n", size);

	print_maps();

	fd = open(FILE_TO_MAP, O_RDONLY);
	mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, pgsz * 2);
	close(fd);

	print_maps();

	/* Make the mem unwritable. */
	mprotect(mem, size / 2, PROT_READ);

	print_maps();

	munmap(mem, size);

	print_maps();

	return 0;
}
