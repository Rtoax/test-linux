#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	int fd = mkfifo("mkfifo.tmp", 1);
	if (fd == -1) {
		fprintf(stderr, "mkfifo: %m\n");
		return -errno;
	}
	unlink("mkfifo.tmp");
	return 0;
}
