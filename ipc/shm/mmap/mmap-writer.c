#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "config.h"

int main(int argc, char *const argv[])
{
	int fd;
	void *mem;
	struct student students[] = {
		{ 1, "Rong Tao", 'm' },
	};

	/* Prepare a file large enough to hold an unsigned integer. */
	fd = open("mmap.out", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

	ftruncate(fd, sizeof(students));

	/* Create the memory mapping. */
	mem = mmap(0, sizeof(students), PROT_WRITE, MAP_SHARED, fd, 0);

	memcpy(mem, students, sizeof(students));

	munmap(mem, FILE_LENGTH);
	close(fd);
	return 0;
}


