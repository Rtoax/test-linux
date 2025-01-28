#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifndef __USE_GNU
#define __USE_GNU
#endif
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#ifndef O_DIRECTORY
#define O_DIRECTORY	00200000	/* must be a directory */
#endif
#ifndef O_TMPFILE
#define O_TMPFILE	020000000 | O_DIRECTORY
#endif

int main(void)
{
	int fd;
	char path[PATH_MAX];

	printf("O_TMPFILE : %0o\n", O_TMPFILE);

	/* O_TMPFILE: Create  an  unnamed  temporary regular file. */
	fd = open("./", O_TMPFILE | O_RDWR, S_IRUSR | S_IWUSR);
	perror("open");

#if 0
	linkat(fd, "", AT_FDCWD, "./tmpfile.txt", AT_EMPTY_PATH);
#else
	/* Create the tmpfile, see open(2)::O_TMPFILE */
	snprintf(path, PATH_MAX,  "/proc/self/fd/%d", fd);
	linkat(AT_FDCWD, path, AT_FDCWD, "./tmpfile.txt", AT_SYMLINK_FOLLOW);
#endif

	close(fd);
	return 0;
}
