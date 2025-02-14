// SPDX-License-Identifier: GPL-3.0
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <argp.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <sched.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <numa.h>
#include <numaif.h>

#if defined(HAVE_MMAP_HELPERS)
#include "mmap_helpers.h"
#define mmap sys_mmap
#define munmap sys_munmap
#endif

#if defined(HAVE_LIB_TEST_LINUX_C)
#include "proc.h"
#endif

#if defined(HAVE_LIB_TEST_LINUX_NUMA)
#include "libnuma.h"
#else
#define phy_addr_numa() (-1)
#define virt_addr_numa() (-1)
#endif

static int run_on_cpu;
static int cpu_numa;

static struct mem {
	int prot;
	int fd; /* file or memfd */
	void *mem;
	size_t sz;
} mem_ro, mem_rw, mem_rw_cow
#ifdef CONFIG_MEMFD_CREATE
, memfd_ro
#endif
;

int mbind_to_numa = false;
int verbose = false;

const char argp_prog_doc[] =
	"USAGE: [-b <mbind>] [-v|--verbose]\n";

static const struct argp_option opts[] = {
	{ "mbind", 'b', "MBIND", 1, "Test mbind" },
	{ "verbose", 'v', "VERBOSE", 1, "Display detail" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'b':
		mbind_to_numa = true;
		break;
	case 'v':
		verbose = true;
		break;
	case ARGP_KEY_ARG:
		argp_usage(state);
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static const struct argp argp = {
	.options = opts,
	.parser = parse_arg,
	.doc = argp_prog_doc,
};


void mem_range_rw(void *mem, size_t sz, bool r, bool w)
{
	size_t i;
	for (i = 0; i < sz; i += getpagesize()) {
		/* Read */
		if (r) {
			volatile char c = *(volatile char *)(mem + i);
			(void)c;
		}
		/* Write */
		if (w)
			*(char *)(mem + i) = 'a';
	}
}

void *map_file_or_anon(const char *file, int ro, int cow, struct mem *m)
{
	void *mem = NULL;
	int i, err, fd = -1, prot;
	struct stat st;
	size_t size;

	if (file) {
		fd = open(file, ro ? O_RDONLY : O_RDWR);
		if (fd == -1) {
			fprintf(stderr, "ERROR: open(%s) %m\n", file);
			return NULL;
		}

		err = stat(file, &st);
		if (err == -1) {
			perror("stat");
			goto done;
		}
		size = st.st_size;
		m->fd = fd;
	} else {
#ifdef CONFIG_MEMFD_CREATE
		fd = memfd_create("anonfile", MFD_CLOEXEC);
		if (fd == -1) {
			fprintf(stderr, "ERROR: memfd_create() %m\n");
			return NULL;
		}
		/* Give a size */
		size = getpagesize() * 10;
		m->fd = fd;
		if (ftruncate(fd, size) == -1) {
			perror("ftruncate");
			goto done;
		}
#endif
	}

	prot = PROT_READ;
	if (!ro)
		prot |= PROT_WRITE;

	/* Only test MAP_PRIVATE */
	mem = mmap(NULL, size, prot, MAP_PRIVATE, m->fd, 0);
	if (mem == MAP_FAILED) {
		perror("mmap");
		mem == NULL;
		goto done;
	}

	mem_range_rw(mem, size, 1, 0);

	if (!ro && cow)
		mem_range_rw(mem, size, 0, 1);

done:
	m->mem = mem;
	m->sz = size;
	m->prot = prot;
	return mem;
}

void *unmap_file_or_anon(struct mem *m)
{
	munmap(m->mem, m->sz);
	close(m->fd);
}

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
int addr_numa(unsigned long pa, unsigned long va)
{
	int paddr_numa, vaddr_numa;

	paddr_numa = phy_addr_numa(pa);
	vaddr_numa = virt_addr_numa(va);

	if (paddr_numa == INVALID_NUMA_ID || vaddr_numa == INVALID_NUMA_ID)
		return -1;

	if (paddr_numa == DMESG_NUMA_MEM_INVALID)
		paddr_numa = vaddr_numa;
	else if (paddr_numa != vaddr_numa) {
		fprintf(stderr, "paddr numa(%d) != vaddr numa(%d)\n", paddr_numa, vaddr_numa);
		abort();
	}
	/* Return any of paddr_numa or vaddr_numa */
	return paddr_numa;
}

void test_mapping_phy_addr(void)
{
	unsigned long va, pa;

	printf("%-16s %-16s %-16s %-8s %-8s %-8s\n", "NAME", "VIRT_ADDR",
		"PHY_ADDR", "MEM_NUMA", "CPU", "CPU_NUMA");
	printf("%-16s %-16s %-16s %-8s %-8s %-8s\n", "----", "---------",
		"--------", "--------", "---", "--------");

#define PR(name, va, pa, numa) do {					\
		printf("%-16s %-16lx %-16lx %-8d %-8d %-8d\n",		\
			name, va, pa, numa, run_on_cpu, cpu_numa);	\
	} while (0)

	va = proc_maps_libc_text_addr(NULL);
	pa = virt_to_phy(va);
	PR("libc text", va, pa, addr_numa(pa, va));

	va = proc_maps_libc_data_addr(NULL);
	pa = virt_to_phy(va);
	PR("libc data", va, pa, addr_numa(pa, va));

	va = proc_maps_exec_text_addr(NULL);
	pa = virt_to_phy(va);
	PR("exec text", va, pa, addr_numa(pa, va));

	va = proc_maps_exec_data_addr(NULL);
	pa = virt_to_phy(va);
	PR("exec data", va, pa, addr_numa(pa, va));

	va = proc_maps_vdso_addr(NULL);
	pa = virt_to_phy(va);
	PR("vdso text", va, pa, addr_numa(pa, va));

	va = proc_maps_vvar_addr(NULL);
	pa = virt_to_phy(va);
	PR("vvar data", va, pa, addr_numa(pa, va));

	va = (unsigned long)mem_ro.mem;
	pa = virt_to_phy(va);
	PR("mem_ro", va, pa, addr_numa(pa, va));

	va = (unsigned long)mem_rw.mem;
	pa = virt_to_phy(va);
	PR("mem_rw", va, pa, addr_numa(pa, va));

	mem_range_rw(mem_rw.mem, mem_rw.sz, 0, 1);

	va = (unsigned long)mem_rw.mem;
	pa = virt_to_phy(va);
	PR("mem_rw(w)", va, pa, addr_numa(pa, va));

	va = (unsigned long)mem_rw_cow.mem;
	pa = virt_to_phy(va);
	PR("mem_rw_cow", va, pa, addr_numa(pa, va));

#ifdef CONFIG_MEMFD_CREATE
	va = (unsigned long)memfd_ro.mem;
	pa = virt_to_phy(va);
	PR("memfd_ro", va, pa, addr_numa(pa, va));
#endif
}

void mem_bind_to_numa(void *mem, size_t size, int dst_numa)
{
	int ret, mode, flags;
	int maxnode;
	struct bitmask *nodemask;

	maxnode = numa_max_node() + 1;
	nodemask = numa_bitmask_alloc(maxnode);

	numa_bitmask_clearall(nodemask);
	numa_bitmask_setbit(nodemask, dst_numa);

	mode = MPOL_BIND;
	flags = MPOL_MF_MOVE | MPOL_MF_STRICT;

	printf("Moving pages via mbind to node %d ...\n", dst_numa);
	ret = mbind(mem, size, mode, nodemask->maskp, nodemask->size, flags);
	if (ret != 0)
		perror("mbind");
}

void mbind_numa(void)
{
	unsigned long va, pa, size, node;

	va = proc_maps_exec_text_addr(&size);
	pa = virt_to_phy(va);
	node = addr_numa(pa, va);
	fprintf(stderr, "Try bind exec text from numa %d to %d with mbind(2)\n",
		node, cpu_numa);
	mem_bind_to_numa((void *)va, size, cpu_numa);

	va = proc_maps_exec_data_addr(&size);
	pa = virt_to_phy(va);
	node = addr_numa(pa, va);
	fprintf(stderr, "Try bind exec data from numa %d to %d with mbind(2)\n",
		node, cpu_numa);
	mem_bind_to_numa((void *)va, size, cpu_numa);

	va = proc_maps_libc_text_addr(&size);
	pa = virt_to_phy(va);
	node = addr_numa(pa, va);
	fprintf(stderr, "Try bind libc text from numa %d to %d with mbind(2)\n",
		node, cpu_numa);
	mem_bind_to_numa((void *)va, size, cpu_numa);

	va = proc_maps_libc_data_addr(&size);
	pa = virt_to_phy(va);
	node = addr_numa(pa, va);
	fprintf(stderr, "Try bind libc data from numa %d to %d with mbind(2)\n",
		node, cpu_numa);
	mem_bind_to_numa((void *)va, size, cpu_numa);
}

#else
#define test_mapping_phy_addr()
#define mbind_numa()
#endif

int main(int argc, char *argv[])
{
	int i, memfd, ret;
	char *buf;
	size_t buf_len;
	unsigned long phy;
	char buffer[1024];

	ret = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (ret) {
		fprintf(stderr, "argp_parse return %d\n", ret);
		return -ret;
	}

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

	mem_ro.mem = map_file_or_anon("/usr/bin/ls", 1, 0, &mem_ro);
	mem_rw.mem = map_file_or_anon("/usr/bin/ls", 0, 0, &mem_rw);
	mem_rw_cow.mem = map_file_or_anon("/usr/bin/ls", 0, 1, &mem_rw_cow);
#ifdef CONFIG_MEMFD_CREATE
	memfd_ro.mem = map_file_or_anon(NULL, 1, 0, &memfd_ro);
#endif

	test_mapping_phy_addr();
	if (mbind_to_numa) {
		mbind_numa();
		test_mapping_phy_addr();
	} else {
		fprintf(stderr, "WARNING: speicy -b,--mbind to test mbind()\n");
	}

/**
 * CONFIG_STRICT_DEVMEM=y is the default kernel configuration in general,
 * disallows to access RAM area via /dev/mem or only allows first 1MB size
 * of RAM.
 */
#if defined(CONFIG_DEVMEM) && !defined(CONFIG_STRICT_DEVMEM)
	buf_len = 1024;

#define BUF_STRING0	"Hello, Original!"
#define BUF_STRING1	"Hello, Memory!"

# ifdef PAGE_ALIGN
	posix_memalign((void **)&buf, 4096, buf_len);
# else
	buf = malloc(buf_len);
# endif
	assert(buf && "malloc failed");

	mlock(buf, buf_len);

	memset(buf, 0x00, buf_len);
	strcpy(buf, BUF_STRING0);

	phy = virt_to_phy((unsigned long)buf);
	printf("%#016lx %#016lx\n", (unsigned long)buf, phy);

	memfd = open_dev_mem();

	dev_mem_read(memfd, phy, buffer, strlen(BUF_STRING0));
	printf("read from /dev/mem buffer %s\n", buffer);
	dev_mem_write(memfd, phy, BUF_STRING1, strlen(BUF_STRING1));
	printf("write to /dev/mem buf %s\n", buf);
	close(memfd);

	free(buf);
#elif defined(CONFIG_STRICT_DEVMEM)
	fprintf(stderr, "CONFIG_STRICT_DEVMEM=y, deny write to /dev/mem!\n");
#endif

	if (verbose) {
#if defined(HAVE_LIB_TEST_LINUX_C)
		proc_pid_maps_display_2(stdout, "virt2phy: ");
#endif
	}

	unmap_file_or_anon(&mem_ro);
	unmap_file_or_anon(&mem_rw);
	unmap_file_or_anon(&mem_rw_cow);
#ifdef CONFIG_MEMFD_CREATE
	unmap_file_or_anon(&memfd_ro);
#endif
	return 0;
}
#endif /* HAVE_MAIN */
