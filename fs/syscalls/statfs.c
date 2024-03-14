#include <stdio.h>
#include <string.h>
#include <sys/statfs.h>

#include "proc.h"


static void mnt_cb(const char *mnt_point)
{
	int ret;
	struct statfs info;

	memset(&info, 0, sizeof(struct statfs));

	ret = statfs(mnt_point, &info);
	if (ret == -1)
		return;

	unsigned long long total_sz = info.f_bsize * info.f_blocks;
	size_t total_sz_MB = total_sz >> 20;
	unsigned long long free_sz = info.f_bfree * info.f_bsize;
	size_t free_sz_MB = free_sz >> 20;

	printf("%-32s %-12ld %-12ld %-6.2lf%%\n",
		mnt_point,
		total_sz_MB, free_sz_MB,
		(total_sz_MB - free_sz_MB) * 1.0 / total_sz_MB * 100.0);

	return;
}

int main(void)
{
	fprintf(stdout, "%-32s %-12s %-12s %-12s\n",
		"FILE", "ALL(MB)", "FREE(MB)", "USE%");

	proc_for_each_mnt_point(mnt_cb);

	return 0;
}

