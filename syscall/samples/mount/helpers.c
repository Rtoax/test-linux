#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <linux/loop.h>
#include <linux/unistd.h>


/* Hope -1 isn't a syscall */
#ifndef __NR_fsopen
#define __NR_fsopen -1
#endif
#ifndef __NR_fsmount
#define __NR_fsmount -1
#endif
#ifndef __NR_fsconfig
#define __NR_fsconfig -1
#endif
#ifndef __NR_move_mount
#define __NR_move_mount -1
#endif

/**
 * kernel commit 24dcb3d90a1f ("vfs: syscall: Add fsopen() to prepare for
 * superblock creation") v5.1-rc1-5-g24dcb3d90a1f
 */
int sys_fsopen(const char *fs_name, unsigned int flags)
{
	return syscall(__NR_fsopen, fs_name, flags);
}

/**
 * kernel commit 93766fbd2696 ("vfs: syscall: Add fsmount() to create a mount
 * for a superblock") v5.1-rc1-8-g93766fbd2696
 */
int sys_fsmount(int fsfd, unsigned int flags, unsigned int ms_flags)
{
	return syscall(__NR_fsmount, fsfd, flags, ms_flags);
}

/**
 * kernel commit ecdab150fddb ("vfs: syscall: Add fsconfig() for configuring
 * and managing a context") v5.1-rc1-7-gecdab150fddb
 */
int sys_fsconfig(int fsfd, unsigned int cmd, const char *key, const void *val,
		 int aux)
{
	return syscall(__NR_fsconfig, fsfd, cmd, key, val, aux);
}

/**
 * kernel commit 2db154b3ea8e ("vfs: syscall: Add move_mount(2) to move mounts
 * around") v5.1-rc1-2-g2db154b3ea8e
 */
int sys_move_mount(int from_dfd, const char *from_pathname, int to_dfd,
		   const char *to_pathname, unsigned int flags)
{
	return syscall(__NR_move_mount, from_dfd, from_pathname, to_dfd,
		       to_pathname, flags);
}

int get_free_dev_loop(void)
{
	int fd;
	int free_nr_loop = -1;

	fd = openat(AT_FDCWD, "/dev/loop-control", O_RDWR | O_CLOEXEC);
	if (fd < 0) {
		perror("openat loop-control failed.");
		exit(1);
	}

	free_nr_loop = ioctl(fd, LOOP_CTL_GET_FREE);
	if (free_nr_loop < 0) {
		perror("ioctl");
		exit(1);
	}
	close(fd);

	fprintf(stderr, "get free /dev/loop%d\n", free_nr_loop);

	return free_nr_loop;
}

int bind_file_with_loop(const char *file, int *pffd, const char *dev_loop,
			int *plfd)
{
/**
 * Since kernel commit 3448914e8cc5 ("loop: Add LOOP_CONFIGURE ioctl")
 * v5.7-rc2-189-g3448914e8cc5
 */
#ifdef LOOP_CONFIGURE
	int ret, ffd, lfd;

	ffd = openat(AT_FDCWD, file, O_RDWR | O_CLOEXEC);
	if (ffd == -1) {
		fprintf(stderr, "openat %s: %m\n", file);
		exit(1);
	}
	lfd = openat(AT_FDCWD, dev_loop, O_RDWR | O_CLOEXEC);
	if (lfd == -1) {
		fprintf(stderr, "openat %s: %m\n", dev_loop);
		exit(1);
	}

	struct loop_config lconfig = {
		.fd = ffd,
		.block_size = 0,
		.info = {
			.lo_offset = 0,
			.lo_number = 0,
			.lo_flags = LO_FLAGS_AUTOCLEAR,
		},
	};
	strncpy((char *)lconfig.info.lo_file_name, file, LO_NAME_SIZE);

	ret = ioctl(lfd, LOOP_CONFIGURE, &lconfig);
	if (ret == -1) {
		perror("ioctl loop failed, ");
		exit(1);
	}

	/* FIXME: Just show loop device */
	system("lsblk");

	*pffd = ffd;
	*plfd = lfd;

	return 0;
#else
	return -ENOSYS;
#endif
}

