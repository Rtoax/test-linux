#include <stdio.h>

#include "numa_mem.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define GB (1024 * 1024 * 1024)

int print_numa_mem(void)
{
	int i;
	struct numa_mem_info *info;

	printf("%-8s %-16s %-16s %-8s\n", "NUMA", "START_ADDR", "END_ADDR", "SIZE(GiB)");
	for (i = 0; i < ARRAY_SIZE(numa_mem_info); i++) {
		info = &numa_mem_info[i];
		printf("%-8d %016lx %016lx %4.4f\n",
			info->nid, info->mem_start, info->mem_end,
			(info->mem_end - info->mem_start) * 1.0 / GB);
	}
	return 0;
}

int phy_addr_numa(unsigned long paddr)
{
	int i;
	int nid = -1;
	struct numa_mem_info *info;

	for (i = 0; i < ARRAY_SIZE(numa_mem_info); i++) {
		info = &numa_mem_info[i];
		if (paddr >= info->mem_start && paddr < info->mem_end) {
			nid = info->nid;
			break;
		}
	}
	return nid;
}

#if defined(TEST_MAIN)
int main(void)
{
	print_numa_mem();
	return 0;
}
#endif
