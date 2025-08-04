// SPDX-License-Identifier: GPL-2.0-or-later
/* fd-based mount test.
 *
 * Copyright (C) 2024 Rong Tao. All Rights Reserved.
 * Copyright (C) 2017 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/unistd.h>
#include <linux/loop.h>
#include <linux/mount.h>

#include "mnt_helpers.h"

#if __GLIBC__ != 2
# error Not support glibc < 2
#endif
#if __GLIBC_MINOR__ < 35
# define fsopen sys_fsopen
# define fsmount sys_fsmount
# define fsconfig sys_fsconfig
# define move_mount sys_move_mount
#endif

#define E(x) do { if ((x) == -1) { perror(#x); exit(1); } } while(0)

static void check_messages(int fd)
{
	char buf[4096];
	int err, n;

	err = errno;

	for (;;) {
		n = read(fd, buf, sizeof(buf));
		if (n < 0)
			break;
		n -= 2;

		switch (buf[0]) {
		case 'e':
			fprintf(stderr, "Error: %*.*s\n", n, n, buf + 2);
			break;
		case 'w':
			fprintf(stderr, "Warning: %*.*s\n", n, n, buf + 2);
			break;
		case 'i':
			fprintf(stderr, "Info: %*.*s\n", n, n, buf + 2);
			break;
		default:
			fprintf(stderr, "Unknown: %*.*s\n", n, n, buf + 2);
			break;
		}
	}

	errno = err;
}

static __attribute__((noreturn))
void mount_error(int fd, const char *s)
{
	check_messages(fd);
	fprintf(stderr, "%s: %m\n", s);
	exit(1);
}

#define E_fsconfig(fd, cmd, key, val, aux)				\
	do {								\
		if (fsconfig(fd, cmd, key, val, aux) == -1) {		\
			fprintf(stderr, "fsconfig: %m\n");		\
			mount_error(fd, key ?: "create");		\
		}							\
	} while (0)

int main(int argc, char *argv[])
{
	int ret, ffd, lfd, fsfd, mfd;
	int free_nr_loop = -1;
	const char *target_dir = "./tmp-dir/";
	char loop[PATH_MAX];

	free_nr_loop = get_free_dev_loop();

	printf("Get free /dev/loop%d\n", free_nr_loop);
	snprintf(loop, sizeof(loop), "/dev/loop%d", free_nr_loop);

	bind_file_with_loop("./fs.ext4", &ffd, loop, &lfd);

	fsfd = fsopen("ext4", 0);
	if (fsfd == -1) {
		perror("fsopen");
		exit(1);
	}

	E_fsconfig(fsfd, FSCONFIG_SET_FLAG, "rw", NULL, 0);
	E_fsconfig(fsfd, FSCONFIG_SET_STRING, "source", loop, 0);
	E_fsconfig(fsfd, FSCONFIG_CMD_CREATE, NULL, NULL, 0);

	mfd = fsmount(fsfd, 0, MOUNT_ATTR_RDONLY);
	if (mfd < 0)
		mount_error(fsfd, "fsmount");
	E(close(fsfd));

	/* check and make directory */
	if (access(target_dir, F_OK)) {
		ret = mkdir(target_dir, 0777);
		if (ret) {
			fprintf(stderr, "mkdir %s %m\n", target_dir);
			exit(1);
		}
	}

	if (move_mount(mfd, "", AT_FDCWD, target_dir, MOVE_MOUNT_F_EMPTY_PATH) < 0) {
		perror("move_mount");
		exit(1);
	}

	E(close(mfd));

	printf("Mount created at %s...\n", target_dir);
	printf("Press <return> to unmount the volume: ");
	getchar();

	umount(target_dir);
	rmdir(target_dir);
	close(ffd);
	close(lfd);
	exit(0);
}
