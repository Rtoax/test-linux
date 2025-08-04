#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/stat.h>

#include "mnt_helpers.h"


int main(int argc, char *argv[])
{
	int ret, ffd, lfd;
	int free_nr_loop;
	char loop[PATH_MAX];
	const char *source = "fs.ext4";
	const char *target_dir = "tmp-dir/";

	free_nr_loop = get_free_dev_loop();

	printf("Get free /dev/loop%d\n", free_nr_loop);
	snprintf(loop, sizeof(loop), "/dev/loop%d", free_nr_loop);

	bind_file_with_loop(source, &ffd, loop, &lfd);

	/* check and make directory */
	if (access(target_dir, F_OK)) {
		ret = mkdir(target_dir, 0777);
		if (ret) {
			fprintf(stderr, "mkdir %s %m\n", target_dir);
			exit(1);
		}
	}

	ret = mount(loop, target_dir, "ext4", 0, NULL);
	if (ret == -1) {
		fprintf(stderr, "mount: %s\n", strerror(errno));
		exit(1);
	}

	printf("Mount created at %s...\n", target_dir);
	printf("Press <return> to unmount the volume: ");
	getchar();

	umount(target_dir);
	rmdir(target_dir);
	close(ffd);
	close(lfd);

	exit(0);
}
