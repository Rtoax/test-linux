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

	/* if size is NULL, skip size option */
	if (sz) {
		/* root */
		sprintf(options, "size=%s,uid=0,gid=0,mode=700", sz);
	} else {
		sprintf(options, "uid=0,gid=0,mode=700");
	}

#ifdef DEBUG
	fprintf(stderr, "mount(tmpfs, %s, ..., %s) %m\n", mountpoint, options);
#endif

	err = mount("tmpfs", mountpoint, "tmpfs", 0, options);
	if (err != 0) {
		fprintf(stderr, "mount(tmpfs, %s, ..., %s) %m\n", mountpoint, options);
		return NULL;
	}
	return mountpoint;
}
