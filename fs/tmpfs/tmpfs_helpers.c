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
