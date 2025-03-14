#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <malloc.h>
#include <numa.h>
#include <numaif.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sched.h>

#include "helpers.h"

static int run_on_cpu;
static int cpu_numa;

int main(int argc, char *argv[])
{
	int i, ret, mode, flags;
	void *mem;
	size_t msize;
	int maxnode;
	struct bitmask *nodemask;

	fprintf(stderr, "\033[1;32mTest\n");
	fprintf(stderr, " $ sudo numactl --membind=2 %s\033[m\n",
		argv[0]);

	run_on_cpu = sched_getcpu();
	cpu_numa = numa_node_of_cpu(run_on_cpu);
	printf("Run on CPU %d, NUMA %d\n", run_on_cpu, cpu_numa);

	/**
	 * MPOL_LOCAL since linux v3.8
	 *
	 * This mode specifies "local allocation"; the memory is allocated on
	 * the node of the CPU that triggered the allocation (the "local node").
	 * The nodemask and maxnode arguments must specify the empty set.
	 */
	mode = MPOL_LOCAL;
	ret = mbind(NULL, 0, mode, NULL, 0, 0);
	if (ret != 0)
		perror("mbind");

	msize = getpagesize() * 10;

	/**
	 * mem must be page alignment.
	 */
#if defined(ALLOC_WITH_MMAP)
	mem = mmap(NULL, msize, PROT_READ | PROT_WRITE,
		   MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
#elif defined(ALLOC_WITH_MALLOC)
	mem = malloc(msize);
#elif defined(ALLOC_WITH_POSIX_MEMALIGN)
	posix_memalign((void **)&mem, getpagesize(), msize);
#else
# error "Must define one of ALLOC_WITH_MMAP,ALLOC_WITH_MALLOC,ALLOC_WITH_POSIX_MEMALIGN"
#endif

	/* _need_ pagefault */
	for (i = 0; i < msize; i += getpagesize())
		*((char *)mem + i) = 'a';


	maxnode = numa_max_node() + 1;
	nodemask = numa_bitmask_alloc(maxnode);

	printf("Number of node %d\n", maxnode);

	numa_bitmask_clearall(nodemask);
	numa_bitmask_setbit(nodemask, cpu_numa);

	mode = MPOL_BIND;
	flags = MPOL_MF_MOVE | MPOL_MF_STRICT;

	printf("Pages now on node %d\n", get_addr_node(mem));

	printf("Moving pages via mbind to node %d ...\n", cpu_numa);
	ret = mbind(mem, msize, mode, nodemask->maskp, nodemask->size, flags);
	if (ret != 0)
		perror("mbind");

	printf("Pages now on node %d\n", get_addr_node(mem));

	if (maxnode > 1) {
		numa_bitmask_clearall(nodemask);
		numa_bitmask_setbit(nodemask, 1);
		printf("Moving pages via mbind to node 1 ...\n");
		ret = mbind(mem, msize, mode, nodemask->maskp, nodemask->size, flags);
		if (ret != 0)
			perror("mbind");

		printf("Pages now on node %d\n", get_addr_node(mem));
	}

#if defined(ALLOC_WITH_MMAP)
	munmap(mem, msize);
#else
	free(mem);
#endif
	return 0;
}
