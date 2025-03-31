#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/mount.h>


const char *create_tmpfs(const char *mountpoint, const char *sz)
{
	int err;
	char options[128];

	/* root */
	sprintf(options, "size=%s,uid=0,gid=0,mode=700", sz);
	err = mount("tmpfs", mountpoint, "tmpfs", 0, options);
	if (err != 0) {
		perror("tmpfs creation failed");
		rmdir(mountpoint);
		return NULL;
	}
	return mountpoint;
}

int main(void)
{
	const char *tmpfs;
	char *mountpoint = NULL;
	char path[PATH_MAX];

	snprintf(path, sizeof(path) - 1, "tmpfs_XXXXXX");

	mountpoint = mkdtemp(path);
	if (!mountpoint){
		return -1;
	}

	tmpfs = create_tmpfs(mountpoint, "1M");
	if (!tmpfs)
		return -1;

	printf("Mount created at %s...\n", tmpfs);
	printf("Press <return> to unmount the volume: ");
	getchar();

	umount(tmpfs);
	rmdir(tmpfs);
	return 0;
}

