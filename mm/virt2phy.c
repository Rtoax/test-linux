// SPDX-License-Identifier: GPL-3.0
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <sched.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <numa.h>

#if defined(HAVE_LIB_TEST_LINUX_C)
#include "proc.h"
#endif

#if defined(HAVE_LIB_TEST_LINUX_NUMA)
#include "libnuma.h"
#else
#define phy_addr_numa() (-1)
#define virt_addr_numa() (-1)
#endif

int run_on_cpu;
int cpu_numa;

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

#if defined(DEBUG)
	fprintf(stderr, "pgsize = %ld, pfn = %lx\n", pagesize, pfn);
#endif

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
#if defined(HAVE_LIB_TEST_LINUX_C)
void test_mapping_phy_addr(void)
{
	unsigned long va, pa;

	printf("%-16s %-16s %-16s %-8s %-8s %-8s\n", "NAME", "VIRT_ADDR",
		"PHY_ADDR", "MEM_NUMA", "CPU", "CPU_NUMA");

#define PR(name, va, pa, numa) do {					\
		int ____n = virt_addr_numa(va);				\
		if (numa != ____n) {					\
			printf("FATAL: get numa conflict(%d!=%d)\n",	\
				numa, ____n);				\
			abort();					\
		}							\
		printf("%-16s %-16lx %-16lx %-8d %-8d %-8d\n",		\
			name, va, pa, numa, run_on_cpu, cpu_numa);	\
	} while (0)

	va = proc_maps_libc_text_addr();
	pa = virt_to_phy(va);
	PR("libc text", va, pa, phy_addr_numa(pa));

	va = proc_maps_libc_data_addr();
	pa = virt_to_phy(va);
	PR("libc data", va, pa, phy_addr_numa(pa));

	va = proc_maps_exec_text_addr();
	pa = virt_to_phy(va);
	PR("exec text", va, pa, phy_addr_numa(pa));

	va = proc_maps_exec_data_addr();
	pa = virt_to_phy(va);
	PR("exec data", va, pa, phy_addr_numa(pa));
}
#else
#define test_mapping_phy_addr()
#endif

int main(int argc, char *argv[])
{
	int i, memfd, ret;
	char *buf;
	size_t buf_len;
	unsigned long phy;
	char buffer[1024];

	if (getuid() != 0) {
		fprintf(stderr, "ERROR: must run with root (sudo).\n");
		exit(1);
	}

	fprintf(stderr, "\033[1;32mTest\n");
	fprintf(stderr, " $ sudo numactl --membind=2 --cpunodebind=2 %s\033[m\n",
		argv[0]);

	run_on_cpu = sched_getcpu();
	cpu_numa = numa_node_of_cpu(run_on_cpu);
	printf("Run on CPU %d, NUMA %d\n", run_on_cpu, cpu_numa);

	test_mapping_phy_addr();

/**
 * CONFIG_STRICT_DEVMEM=y is the default kernel configuration in general,
 * disallows to access RAM area via /dev/mem or only allows first 1MB size
 * of RAM.
 */
#if defined(CONFIG_DEVMEM) && !defined(CONFIG_STRICT_DEVMEM)
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

	memfd = open_dev_mem();

	dev_mem_read(memfd, phy, buffer, strlen(BUF_STRING0));
	printf("buffer %s\n", buffer);
	dev_mem_write(memfd, phy, BUF_STRING1, strlen(BUF_STRING1));
	printf("buf = %s\n", buf);
	close(memfd);

	free(buf);
#endif

	return 0;
}
#endif /* HAVE_MAIN */
