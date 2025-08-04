#include <stdio.h>
#include <string.h>
#include <sys/statfs.h>

#include "proc_helpers.h"


static void mountpoint_statfs_callback(const struct proc_mountpoint *mnt)
{
	int ret;
	size_t total_sz, free_sz;
	struct statfs info;
	const char *mnt_point = mnt->mountpoint;

	memset(&info, 0, sizeof(struct statfs));

	ret = statfs(mnt_point, &info);
	if (ret == -1)
		return;

	total_sz = info.f_bsize * info.f_blocks;
	/* B to MB */
	total_sz >>= 20;
	free_sz = info.f_bfree * info.f_bsize;
	free_sz >>= 20;

	printf("%-32s %-12ld %-12ld %-6.2lf%%\n", mnt_point, total_sz, free_sz,
		(total_sz - free_sz) * 1.0 / total_sz * 100.0);
}

int main(void)
{
	fprintf(stdout, "%-32s %-12s %-12s %-12s\n",
		"FILE", "ALL(MB)", "FREE(MB)", "USE%");

	proc_for_each_mount(mountpoint_statfs_callback);

	return 0;
}

