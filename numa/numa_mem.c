#include <stdio.h>
#include <numaif.h>
#include <numa.h>

#include "libnuma.h"
#include "numa_mem.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define GB (1024 * 1024 * 1024)

int print_numa_mem(void)
{
	int i;
	struct numa_mem_info *info;

	if (ARRAY_SIZE(numa_mem_info) == 0)
		return DMESG_NUMA_MEM_INVALID;

	printf("%-8s %-16s %-16s %-8s\n", "NUMA", "START_ADDR", "END_ADDR", "SIZE(GiB)");
	for (i = 0; i < ARRAY_SIZE(numa_mem_info); i++) {
		info = &numa_mem_info[i];
		printf("%-8d %016lx %016lx %4.4f\n",
			info->nid, info->mem_start, info->mem_end,
			(info->mem_end + 1 - info->mem_start) * 1.0 / GB);
	}
	return ARRAY_SIZE(numa_mem_info);
}

/**
 * Return numa id, return -1 if failed
 */
int phy_addr_numa(unsigned long paddr)
{
	int i;
	int nid = INVALID_NUMA_ID;
	struct numa_mem_info *info;

	/* If only one of NUMA node, just return 0 */
	if (numa_max_node() == 0)
		return 0;

	if (ARRAY_SIZE(numa_mem_info) == 0)
		return DMESG_NUMA_MEM_INVALID;

	for (i = 0; i < ARRAY_SIZE(numa_mem_info); i++) {
		info = &numa_mem_info[i];
		if (paddr >= info->mem_start && paddr <= info->mem_end) {
			nid = info->nid;
			break;
		}
	}
	return nid;
}

int virt_addr_numa(unsigned long vaddr)
{
	int ret, flags, mode;

	/* If only one of NUMA node, just return 0 */
	if (numa_max_node() == 0)
		return 0;

	flags = MPOL_F_NODE | MPOL_F_ADDR;
	ret = get_mempolicy(&mode, NULL, 0, (void *)vaddr, flags);
	if (ret != 0) {
#ifdef DEBUG
		fprintf(stderr, "get_mempolicy vaddr %lx: %m\n", vaddr);
#endif
		return INVALID_NUMA_ID;
	}
	return mode;
}

#if defined(TEST_MAIN)
int main(void)
{
	print_numa_mem();
	return 0;
}
#endif
