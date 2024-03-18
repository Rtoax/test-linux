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

#include "helpers.h"


int main(int argc, char *argv[])
{
	int ret, ffd, lfd;
	int free_nr_loop;
	char loop[PATH_MAX];
	const char *source = "fs.ext4";
	const char *target = "tmp-dir/";

	free_nr_loop = get_free_dev_loop();

	printf("Get free /dev/loop%d\n", free_nr_loop);
	snprintf(loop, sizeof(loop), "/dev/loop%d", free_nr_loop);

	bind_file_with_loop(source, &ffd, loop, &lfd);

	ret = mount(loop, target, "ext4", 0, NULL);
	if (ret == -1) {
		fprintf(stderr, "mount: %s\n", strerror(errno));
		exit(1);
	}

	printf("Mount created at %s...\n", target);
	printf("Press <return> to unmount the volume: ");
	getchar();

	umount(target);
	rmdir(target);
	close(ffd);
	close(lfd);

	exit(0);
}

