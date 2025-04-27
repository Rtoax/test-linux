#include <stdio.h>
#include <errno.h>
#include <numa.h>
#include <numaif.h>

#include "numa_helpers.h"

int tl_numa_available(void)
{
	if (get_mempolicy(NULL, NULL, 0, 0, 0) < 0 && (errno == ENOSYS || errno == EPERM))
		return -1;
	return 0;
}

int main(int argc, char *argv[])
{
	int ret, mode, flags;
	unsigned long nodemask[4], maxnode;
	char *mem;
	size_t size;

	fprintf(stderr, "\033[1;32mTest\n");
	fprintf(stderr, " $ numactl --membind=2,3 %s\033[m\n",
		argv[0]);

	maxnode = sizeof(nodemask);

	ret = tl_numa_available();
	printf("tl_numa_available return %d\n", ret);

	memset(nodemask, 0x00, sizeof(nodemask));

	/**
	 * If flags is specified as 0, then information about the calling
	 * thread's default policy (as set by set_mempolicy(2)) is returned,
	 * in the buffers pointed to by mode and nodemask.
	 */
	flags = 0;
	ret = get_mempolicy(&mode, nodemask, maxnode, NULL, flags);
	if (ret != 0)
		perror("get_mempolicy1");
	print_nodemask("default nodemask: ", nodemask, maxnode);

	/**
	 * If flags specifies MPOL_F_MEMS_ALLOWED (available since Linux 2.6.24),
	 * the mode argument is ignored and the set of nodes (memories) that
	 * the thread is allowed to specify in subsequent calls to mbind(2)
	 * or set_mempolicy(2) (in the absence of any mode flags) is returned
	 * in nodemask.
	 */
	flags = MPOL_F_MEMS_ALLOWED;
	ret = get_mempolicy(NULL, nodemask, maxnode, NULL, flags);
	if (ret != 0)
		perror("get_mempolicy2");
	print_nodemask("allowed nodemask: ", nodemask, maxnode);

	/**
	 * If flags specifies MPOL_F_ADDR, then information is returned about
	 * the policy governing the memory address given in addr.
	 */
	size = 1024;
	mem = numa_alloc(size);
	flags = MPOL_F_ADDR;
	ret = get_mempolicy(&mode, NULL, 0, mem, flags);
	if (ret != 0)
		perror("get_mempolicy3");
	printf("mem(%p) policy is ", mem);
	print_mpol(mode);

	/**
	 * If flags specifies both MPOL_F_NODE and MPOL_F_ADDR, get_mempolicy()
	 * will return the node ID of the node on which the address addr is
	 * allocated into the location pointed to by mode.
	 */
	flags = MPOL_F_NODE | MPOL_F_ADDR;
	ret = get_mempolicy(&mode, NULL, 0, mem, flags);
	if (ret != 0)
		perror("get_mempolicy4");
	printf("mem(%p) in numa %d\n", mem, mode);

	numa_free(mem, size);

	return 0;
}
