#include <stdio.h>

#include "numa_mem.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define GB (1024 * 1024 * 1024)

int main(void)
{
	int i;
	struct numa_mem_info *info;

	for (i = 0; i < ARRAY_SIZE(numa_mem_info); i++) {
		info = &numa_mem_info[i];
		printf("%-8d %016lx %016lx %4.4f GiB\n",
			info->nid, info->mem_start, info->mem_end,
			(info->mem_end - info->mem_start) * 1.0 / GB);
	}
	return 0;
}
