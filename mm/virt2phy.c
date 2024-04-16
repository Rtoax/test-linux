#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * https://www.kernel.org/doc/Documentation/vm/pagemap.txt
 */
unsigned long virt_to_phy(unsigned long vaddr)
{
	int fd;
	off_t ret;
	unsigned long pfn = 0;
	ssize_t rc;
	unsigned long pagesize = sysconf(_SC_PAGESIZE);

	/* Get page frame number of address */
	fd = open("/proc/self/pagemap", O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "open /proc/self/pagemap: %m\n");
		goto failed;
	}

	ret = lseek(fd, vaddr / pagesize * sizeof(unsigned long), SEEK_SET);
	if (ret == -1) {
		fprintf(stderr, "lseek: %m\n");
		goto failed;
	}

	rc = read(fd, &pfn, sizeof(pfn));
	if (rc < sizeof(pfn) || pfn == 0) {
		fprintf(stderr, "read: %m\n");
		goto failed;
	}

	close(fd);
	return (pfn & 0x7fffffffffffffULL) * pagesize + vaddr % pagesize;

failed:
	close(fd);
	return 0;
}

int main(void)
{
	int i;
	printf("%#016lx %#016lx\n", &i, virt_to_phy((unsigned long)&i));
	return 0;
}
