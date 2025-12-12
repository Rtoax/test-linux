#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <malloc.h>
#include <pthread.h>
#include <numa.h>
#include <numaif.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sched.h>

#include "numa_helpers.h"

void *task_busy_write_page(void *arg)
{
	int i;
	char *mem = arg;
	size_t pagesz = getpagesize();
	while (1) {
		for (i = 0; i < pagesz; i++) {
			mem[i] = 'a';
		}
	}
}

void busy_write(void *mem)
{
	pthread_t thread;
	pthread_create(&thread, NULL, task_busy_write_page, mem);
}

int main(int argc, char *argv[])
{
	int i, ret, mode;
	void *mem;
	size_t msize, pages;
	int maxnode;
	int run_on_cpu;
	int cpu_numa, page_numa;

	struct bitmask *nodemask;

	fprintf(stderr, "\033[1;32mTest\n");
	fprintf(stderr, " $ sudo numactl --cpunodebind=1 --membind=2 %s\033[m\n",
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
	if (ret != 0) {
		perror("mbind");
		exit(1);
	}

	pages = 10;
	msize = getpagesize() * pages;

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

#if 1
	/* _need_ pagefault */
	for (i = 0; i < msize; i += getpagesize())
		*((char *)mem + i) = 'a';
#endif

	maxnode = numa_max_node() + 1;
	printf("Number of node %d\n", maxnode);

	nodemask = numa_bitmask_alloc(maxnode);

	page_numa = get_addr_node(mem);
	printf("Pages now on node %d\n", page_numa);

	if (cpu_numa != page_numa) {
		printf("Moving pages via mbind() from node %d to %d ...\n", page_numa, cpu_numa);
		numa_bitmask_clearall(nodemask);
		numa_bitmask_setbit(nodemask, cpu_numa);
		ret = mbind(mem, msize, MPOL_BIND, nodemask->maskp, nodemask->size,
				MPOL_MF_MOVE | MPOL_MF_STRICT);
		if (ret != 0) {
			fprintf(stderr, "mbind() failed, %m\n");
			goto done;
		}

		page_numa = get_addr_node(mem);
		printf("Pages now on node %d\n", page_numa);
	}

	/**
	 * Test move_pages(2)
	 */
	if (maxnode > 1) {
		int *nodes = (int *)malloc(sizeof(int) * pages);
		int *status = (int *)malloc(sizeof(int) * pages);
		void **pages_ptr = (void **)malloc(sizeof(void *) * pages);
		for (i = 0; i < pages; i++) {
			nodes[i] = i % maxnode;
			status[i] = 0;

			/* Bad address */
			if (i == 1)
				pages_ptr[i] = NULL;
			/* OK */
			else if (i == 2)
				pages_ptr[i] = main;
			else
				pages_ptr[i] = mem + i * getpagesize();

			/* busy write the 4th page */
			if (i == 3) {
				busy_write(pages_ptr[i]);
				usleep(100000);
			}

			printf("Moving page %p via move_pages() from numa %d to %d\n",
				pages_ptr[i],
				get_addr_node(pages_ptr[i]),
				nodes[i]);
		}
		ret = move_pages(0, pages, pages_ptr, nodes, status, MPOL_MF_MOVE | MPOL_MF_MOVE_ALL);
		if (ret != 0) {
			fprintf(stderr, "move_pages failed(ret=%d): %m\n", ret);
			goto move_pages_failed;
		}
		for (i = 0; i < pages; i++) {
			if (status[i] < 0)
				printf("Move page %p failed: %s\n", pages_ptr[i], strerror(-status[i]));
			else {
				int policy_node = get_addr_node(pages_ptr[i]);
				printf("Move page %p to numa %d (%d) success\n",
					pages_ptr[i], status[i], policy_node);
			}
		}
move_pages_failed:
		free(pages_ptr);
		free(nodes);
		free(status);
	}

done:
#if defined(ALLOC_WITH_MMAP)
	munmap(mem, msize);
#else
	free(mem);
#endif
	return 0;
}
