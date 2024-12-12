/**
 * How to mount cgroupv2
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mount.h>

int mount_cgroupv2(const char *dst_path)
{
	int err;

	/**
	 * Create target directory if not exist.
	 */
	err = access(dst_path, F_OK);
	if (err) {
		fprintf(stderr, "directory %s is not exist.\n", dst_path);
		err = mkdir(dst_path, 0777);
		if (err) {
			fprintf(stderr, "couldn't mkdir %s: %m\n", dst_path);
			return errno;
		}
	}

	err = mount("none", dst_path, "cgroup2", 0, NULL);
	if (err && errno != EBUSY) {
		fprintf(stderr, "mount cgroup2: %m\n");
		return errno;
	}
	return 0;
}

#ifdef TEST_MAIN
#define DST	"a.mnt"
int main(void)
{
	int err;
	const char *dst = DST;

	mkdir(dst, 0777);

	err = mount_cgroupv2(dst);
	if (err)
		return -1;

	system("ls "DST);

	usleep(100000);

	err = umount(dst);
	if (err) {
		fprintf(stderr, "umount %s : %m\n", dst);
		return -1;
	}

	system("ls "DST);
	rmdir(dst);

	return 0;
}
#endif
