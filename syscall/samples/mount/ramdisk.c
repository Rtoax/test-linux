#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/mount.h>

#include "tmpfs_helpers.h"


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
	printf("Press <return> to unmount the volume: ");
	getchar();

	umount(tmpfs);
	rmdir(tmpfs);
	return 0;
}

