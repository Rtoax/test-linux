#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/wait.h>

#include "flock_helpers.h"


/**
 * duplicate file descriptors (created by, for example, fork(2) or dup(2))
 * refer to the same lock. (see flock(2))
 */
int open_and_write_with_lock(const char *filename, const char *prefix,
			     const char *msg)
{
	int ret;
	int fd = open(filename, O_TRUNC | O_RDWR, 0644);

	ret = flock(fd, LOCK_EX | LOCK_NB);
	if (ret != 0) {
		fprintf(stderr, "[%s] flock: %s\n", prefix, strerror(errno));
		close(fd);
		return -1;
	}

	write(fd, msg, strlen(msg));

	flock(fd, LOCK_UN);
	close(fd);

	return 0;
}
