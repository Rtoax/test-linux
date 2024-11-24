#include <stdio.h>

#include "numa_mem.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

int main(void)
{
	int i;
	struct numa_mem_info *info;

	for (i = 0; i < ARRAY_SIZE(numa_mem_info); i++) {
		info = &numa_mem_info[i];
		printf("%-8d %016lx %016lx\n", info->nid, info->mem_start, info->mem_end);
	}
	return 0;
}
