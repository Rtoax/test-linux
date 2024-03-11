#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <syscall.h>
#include <unistd.h>


int do_statx(int dfd, const char *path, int flags, unsigned mask,
	     struct statx *statxbuf)
{
	return syscall(__NR_statx, dfd, path, flags, mask, statxbuf);
}

int main(int argc, char *argv[])
{
	struct statx buf;
	const char *filename = "/etc/os-release";

	statx(-1, filename, 0, STATX_ALL, &buf);

	printf("mode: %x\n", buf.stx_mode);
	printf("ino: %lld\n", buf.stx_ino);

	if (buf.stx_mode & S_IWUSR)
		printf("Owning user can write `%s'.\n", filename);

	return 0;
}
