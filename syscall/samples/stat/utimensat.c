/**
 * see also touch(1)
 */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	const char *filename = argv[0];
	struct timespec times[2];

	/**
	 * access time
	 *
	 * $ sudo touch -a -d '2025-03-21 15:32:16' [FILE]
	 */
	times[0].tv_sec = time(NULL) - 3600 * 24;
	times[0].tv_nsec = 0;

	/**
	 * modify time
	 *
	 * $ sudo touch -m -d '2025-03-31 15:32:16' [FILE]
	 */
	times[1].tv_sec = time(NULL) - 3600 * 24;
	times[1].tv_nsec = 0;

	/**
	 * NOTE: if you want to change "ctime", you could use chmod/chown.
	 */

#ifdef FUTIMENS
	fprintf(stderr, "Test futimens.\n");

	int fd = open(filename, O_RDONLY);
	if (futimens(fd, times) == -1) {
		perror("futimens");
		close(fd);
		return 1;
	}
	close(fd);
#else
	fprintf(stderr, "Test utimensat.\n");

	if (utimensat(AT_FDCWD, filename, times, 0) == -1) {
		perror("utimensat");
		return 1;
	}
#endif

	printf("Success modify %s's atime and mtime\n", filename);
	return 0;
}
