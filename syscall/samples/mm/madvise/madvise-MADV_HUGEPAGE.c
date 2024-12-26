#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>

#ifdef POSIX
#define madvise posix_madvise
#endif

typedef struct {
	char name[32];
	int age;
} people;

int main(int argc, char *argv[])
{
	int fd, i, ret;
	people *p_map;
	size_t size;

	fd = open("/dev/zero", O_CREAT | O_RDWR, 00777);
	size = sizeof(people) * 1024;

	p_map = (people *) mmap(NULL, size, PROT_READ | PROT_WRITE,
				MAP_SHARED, fd, 0);
	if (p_map == MAP_FAILED) {
		fprintf(stderr, "mmap: %s\n", strerror(errno));
		return -1;
	}

	ret = madvise(p_map, size, MADV_HUGEPAGE);
	if (ret) {
		perror("madvise");
		return ret;
	}

	/* pagefault */
	for (i = 0; i < size / sizeof(people); i++) {
		people *p = p_map + i;
		snprintf(p->name, sizeof(p->name), "name/%d", i);
		p->age = 18;
		printf("name: %s age:%d\n", p->name, p->age);
	}

	munmap(p_map, size);

	return 0;
}
