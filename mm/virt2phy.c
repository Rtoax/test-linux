// SPDX-License-Identifier: GPL-3.0
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

#if defined(HAVE_LIB_TEST_LINUX_C)
#include "proc.h"
#endif

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
		fprintf(stderr, "ERROR: open /proc/self/pagemap: %m\n");
		goto failed;
	}

	ret = lseek(fd, vaddr / pagesize * sizeof(unsigned long), SEEK_SET);
	if (ret == -1) {
		fprintf(stderr, "ERROR: lseek: %m\n");
		goto failed;
	}

	rc = read(fd, &pfn, sizeof(pfn));
	if (rc < sizeof(pfn) || pfn == 0) {
		fprintf(stderr, "ERROR: read: %m\n");
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

int open_dev_mem(void)
{
	int memfd;
	memfd = open("/dev/mem", O_RDWR);
	if (memfd == -1) {
		fprintf(stderr, "ERROR: open /dev/mem: %m\n");
		exit(1);
	}
	return memfd;
}

int dev_mem_write(int memfd, unsigned long phyaddr, void *buf, size_t buf_len)
{
	int ret = 0;
	ret = lseek(memfd, phyaddr, SEEK_SET);
	if (ret == -1) {
		fprintf(stderr, "ERROR: lseek /dev/mem: %m\n");
		exit(1);
	}
	ret = write(memfd, buf, buf_len);
	if (ret == -1) {
		fprintf(stderr, "ERROR: write /dev/mem: %m\n");
		exit(1);
	}

	return ret;
}

int dev_mem_read(int memfd, unsigned long phyaddr, void *to_buf, size_t len)
{
	int ret = 0;
	ret = lseek(memfd, phyaddr, SEEK_SET);
	if (ret == -1) {
		fprintf(stderr, "ERROR: lseek /dev/mem: %m\n");
		exit(1);
	}
	ret = read(memfd, to_buf, len);
	if (ret == -1) {
		fprintf(stderr, "ERROR: read /dev/mem: %m\n");
		exit(1);
	}

	return ret;
}

#if defined(HAVE_MAIN)
int main(void)
{
	int i, memfd, ret;
	char *buf;
	size_t buf_len;
	unsigned long phy;
	char buffer[1024];

#if defined(HAVE_LIB_TEST_LINUX_C)
	unsigned long text_addr, data_addr;
	text_addr = proc_maps_libc_text_addr();
	printf("libc text addr : %lx (phy %lx)\n", text_addr, virt_to_phy(text_addr));
	data_addr = proc_maps_libc_data_addr();
	printf("libc data addr : %lx (phy %lx)\n", data_addr, virt_to_phy(data_addr));
	text_addr = proc_maps_exec_text_addr();
	printf("exec text addr : %lx (phy %lx)\n", text_addr, virt_to_phy(text_addr));
	data_addr = proc_maps_exec_data_addr();
	printf("exec data addr : %lx (phy %lx)\n", data_addr, virt_to_phy(data_addr));
#endif

	memfd = open_dev_mem();

	buf_len = 1024;

#define BUF_STRING0	"Hello, Original!"
#define BUF_STRING1	"Hello, Memory!"

#ifdef PAGE_ALIGN
	posix_memalign((void **)&buf, 4096, buf_len);
#else
	buf = malloc(buf_len);
#endif
	assert(buf && "malloc failed");

	mlock(buf, buf_len);

	memset(buf, 0x00, buf_len);
	strcpy(buf, BUF_STRING0);

	phy = virt_to_phy((unsigned long)buf);
	printf("%#016lx %#016lx\n", (unsigned long)buf, phy);

#if 0
	dev_mem_read(memfd, phy, buffer, strlen(BUF_STRING0));
	printf("buffer %s\n", buffer);
#endif
	dev_mem_write(memfd, phy, BUF_STRING1, strlen(BUF_STRING1));

	printf("buf = %s\n", buf);

exit:
	free(buf);
	close(memfd);

	return 0;
}
#endif /* HAVE_MAIN */
