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
 * https://www.kernel.org/doc/Documentation/vm/pagemap.txt
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

#ifdef DPDK
#define phys_addr_t uint64_t
#define RTE_BAD_IOVA	0
#define RTE_LOG(...)
#define PFN_MASK_SIZE	8
int phys_addrs_available = 1;

phys_addr_t
rte_mem_virt2phy(const void *virtaddr)
{
	int fd, retval;
	uint64_t page, physaddr;
	unsigned long virt_pfn;
	int page_size;
	off_t offset;

	if (phys_addrs_available == 0)
		return RTE_BAD_IOVA;

	/* standard page size */
	page_size = getpagesize();

	fd = open("/proc/self/pagemap", O_RDONLY);
	if (fd < 0) {
		RTE_LOG(INFO, EAL, "%s(): cannot open /proc/self/pagemap: %s\n",
			__func__, strerror(errno));
		return RTE_BAD_IOVA;
	}

	virt_pfn = (unsigned long)virtaddr / page_size;
	offset = sizeof(uint64_t) * virt_pfn;
	if (lseek(fd, offset, SEEK_SET) == (off_t) -1) {
		RTE_LOG(INFO, EAL, "%s(): seek error in /proc/self/pagemap: %s\n",
				__func__, strerror(errno));
		close(fd);
		return RTE_BAD_IOVA;
	}

	retval = read(fd, &page, PFN_MASK_SIZE);
	close(fd);
	if (retval < 0) {
		RTE_LOG(INFO, EAL, "%s(): cannot read /proc/self/pagemap: %s\n",
				__func__, strerror(errno));
		return RTE_BAD_IOVA;
	} else if (retval != PFN_MASK_SIZE) {
		RTE_LOG(INFO, EAL, "%s(): read %d bytes from /proc/self/pagemap "
				"but expected %d:\n",
				__func__, retval, PFN_MASK_SIZE);
		return RTE_BAD_IOVA;
	}

	/*
	 * the pfn (page frame number) are bits 0-54 (see
	 * pagemap.txt in linux Documentation)
	 */
	if ((page & 0x7fffffffffffffULL) == 0)
		return RTE_BAD_IOVA;

	physaddr = ((page & 0x7fffffffffffffULL) * page_size)
		+ ((unsigned long)virtaddr % page_size);

	return physaddr;
}
#else
#define rte_mem_virt2phy(...)	0UL
#endif

int main(void)
{
	int i, fd, ret;
	char *buf;
	unsigned long phy;

	fd = open("/dev/mem", O_RDWR);
	if (fd == -1) {
		fprintf(stderr, "open /dev/mem: %m\n");
		exit(1);
	}

	buf = malloc(1024);
	assert(buf && "malloc failed");

	mlock(buf, 1024);

	memset(buf, 0x00, 1024);

	phy = virt_to_phy((unsigned long)buf);
	printf("%#016lx %#016lx %#016lx\n", (unsigned long)buf, phy, rte_mem_virt2phy(buf));

	ret = lseek(fd, phy, SEEK_SET);
	if (ret == -1) {
		fprintf(stderr, "lseek /dev/mem: %m\n");
		goto exit;
	}

#define BUF_STRING	"Hello, Memory!"
	ret = write(fd, BUF_STRING, strlen(BUF_STRING));
	if (ret < strlen(BUF_STRING)) {
		fprintf(stderr, "write /dev/mem: %m\n");
		goto exit;
	}

	printf("buf = %s\n", buf);

exit:
	free(buf);
	close(fd);

	return 0;
}
