#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <linux/memfd.h>

#include "memfd_helpers.h"


int anonyexec(const char *path, char *argv[])
{
	int fd, fdm, filesize;
	void *elfbuf;
	char cmdline[256];

	/* Open elf file */
	fd = open(path, O_RDONLY);
	filesize = lseek(fd, SEEK_SET, SEEK_END);
	lseek(fd, SEEK_SET, SEEK_SET);

	elfbuf = malloc(filesize);
	read(fd, elfbuf, filesize);
	close(fd);

	/* Create memfd and copy ELF into it. */
	fdm = sys_memfd_create("elf", MFD_CLOEXEC);
	ftruncate(fdm, filesize);
	write(fdm, elfbuf, filesize);
	free(elfbuf);

	/* Exec ELF in memory */
	sprintf(cmdline, "/proc/self/fd/%d", fdm);
	argv[0] = cmdline;
	execve(argv[0], argv, NULL);

	return -1;
}

int main(void)
{
	int ret;
	char *argv[] = { "/bin/uname", "-a", NULL };

	ret = anonyexec("/bin/uname", argv);

	return ret;
}
