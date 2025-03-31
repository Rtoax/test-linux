#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/mount.h>


char *ramdisk(const char *ns, const char *sz)
{
	int rc;
	char *mountpoint = NULL, *options = NULL;
	char path[PATH_MAX];

	memset(path, 0, sizeof(path));

	const char *tmpdir = getenv("TMPDIR");
	if (!tmpdir){
		tmpdir = "/tmp/";
	}

	snprintf(path, sizeof(path) - 1, "%s%s_XXXXXX", tmpdir, ns);

	mountpoint = mkdtemp(path);
	if (!mountpoint){
		return NULL;
	}

	/* root */
	asprintf(&options, "size=%s,uid=0,gid=0,mode=700", sz);
	rc = mount("tmpfs", mountpoint, "tmpfs", 0, options);
	free(options);

	if (rc != 0) {
		perror("tmpfs creation failed");
		rmdir(mountpoint);
		return NULL;
	}
	return strdup(mountpoint);
}

int main(void)
{
	char *tmpfs;

	tmpfs = ramdisk("ramdisk", "1M");
	if (!tmpfs)
		return -1;

	printf("Mount created at %s...\n", tmpfs);
	printf("Press <return> to unmount the volume: ");
	getchar();

	umount(tmpfs);

	rmdir(tmpfs);
	free(tmpfs);
	return 0;
}

