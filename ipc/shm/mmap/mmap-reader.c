#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "config.h"

int main(int argc, char *const argv[])
{
	int fd;
	void *mem;
	struct student *student;

	fd = open("mmap.out", O_RDONLY);

	mem = mmap(0, sizeof(student), PROT_READ, MAP_SHARED, fd, 0);
	if (mem == MAP_FAILED) {
		fprintf(stderr, "mmap failed.\n");
		exit(1);
	}

	student = (struct student *)mem;

	printf("%-8d %-16s %c\n", student->no, student->name, student->sex);

	munmap(mem, FILE_LENGTH);
	close(fd);
	return 0;
}
