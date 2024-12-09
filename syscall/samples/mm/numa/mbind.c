#include <stdio.h>
#include <malloc.h>
#include <numa.h>
#include <numaif.h>
#include <unistd.h>
#include <sys/mman.h>


int get_addr_node(void *vaddr)
{
	int ret, flags, mode;
	flags = MPOL_F_NODE | MPOL_F_ADDR;
	ret = get_mempolicy(&mode, NULL, 0, (void *)vaddr, flags);
	if (ret != 0)
		perror("get_mempolicy");
	return mode;
}

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
	numa_bitmask_setbit(nodemask, 0);

	mode = MPOL_BIND;
	flags = MPOL_MF_MOVE | MPOL_MF_STRICT;

	printf("Pages now on node %d\n", get_addr_node(mem));

	printf("Moving pages via mbind to node 0 ...\n");
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
