#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>

/**
 * refs:
 * - https://www.kernel.org/doc/Documentation/vm/pagemap.txt
 * - dpdk: rte_mem_virt2phy()
 */
unsigned long virt_to_phy(unsigned long vaddr)
{
	int fd;
	off_t ret;
	unsigned long pfn = 0;
	ssize_t rc;
	unsigned long pagesize = sysconf(_SC_PAGESIZE);
	unsigned int offset;

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
	pfn &= 0x7fffffffffffffULL;

	fprintf(stderr, "pgsize = %ld, pfn = %lx\n", pagesize, pfn);

	close(fd);

	offset = (unsigned long)vaddr % pagesize;
	return pfn * pagesize + offset;

failed:
	close(fd);
	return 0;
}

int main(void)
{
	int i, memfd, ret;
	char *buf;
	unsigned long phy;

	memfd = open("/dev/mem", O_RDWR);
	if (memfd == -1) {
		fprintf(stderr, "open /dev/mem: %m\n");
		exit(1);
	}

#ifdef PAGE_ALIGN
	posix_memalign((void **)&buf, 4096, 1024);
#else
	buf = malloc(1024);
#endif
	assert(buf && "malloc failed");

	mlock(buf, 1024);

	memset(buf, 0x00, 1024);

	phy = virt_to_phy((unsigned long)buf);
	printf("%#016lx %#016lx\n", (unsigned long)buf, phy);

	ret = lseek(memfd, phy, SEEK_SET);
	if (ret == -1) {
		fprintf(stderr, "lseek /dev/mem: %m\n");
		goto exit;
	}

#define BUF_STRING	"Hello, Memory!"
	ret = write(memfd, BUF_STRING, strlen(BUF_STRING));
	if (ret == -1) {
		fprintf(stderr, "write /dev/mem: %m\n");
		goto exit;
	}

	printf("buf = %s\n", buf);

exit:
	free(buf);
	close(memfd);

	return 0;
}
