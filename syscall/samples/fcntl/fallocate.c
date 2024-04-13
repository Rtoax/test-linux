#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define TEST_FILE	"a.txt"

int main(int argc, char *argv[])
{
	int fd = open(TEST_FILE, O_CREAT | O_RDWR, 0644);

	/**
	 * Tracing: sudo bpftrace -e 'kprobe:*_fallocate { @[probe] = count() }'
	 *
	 * This is a nonportable, Linux-specific system call. For the portable,
	 * POSIX.1-specified method of ensuring that space is allocated for a
	 * file, see posix_fallocate(3). See fallocate(2).
	 */
	fallocate(fd, 0, 0, 1024);

	posix_fallocate(fd, 0, 1024);

	close(fd);
	return 0;
}
