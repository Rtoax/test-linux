#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/mount.h>
#include <sys/statfs.h>

#include "tmpfs_helpers.h"


static void mountpoint_statfs(const char *mnt_point)
{
	size_t total_sz, free_sz;
	struct statfs info;
	statfs(mnt_point, &info);

	total_sz = info.f_bsize * info.f_blocks;
	/* B to MB */
	total_sz >>= 20;
	free_sz = info.f_bfree * info.f_bsize;
	free_sz >>= 20;

	printf("mountpoint %s, total %ld MB, free %ld MB\n", mnt_point, total_sz, free_sz);
}

int main(void)
{
	const char *tmpfs;
	char *mountpoint = NULL;
	char path[PATH_MAX];

	snprintf(path, sizeof(path) - 1, "tmpfs-XXXXXX");

	mountpoint = mkdtemp(path);
	if (!mountpoint){
		return -1;
	}

	tmpfs = create_tmpfs(mountpoint, "64G");
	if (!tmpfs)
		return -1;

	printf("Mount created at %s...\n", tmpfs);
	mountpoint_statfs(tmpfs);
	printf("Press <return> to unmount the volume: ");

	getchar();

	umount(tmpfs);
	rmdir(tmpfs);
	return 0;
}
