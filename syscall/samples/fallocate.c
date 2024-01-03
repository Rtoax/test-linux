/**
 * File: fallocate.c
 * Author: Rong Tao
 * Date: 2022-09-06
 *
 * Description: Test syscall fallocate(2)
 * Ref:
 */
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
	 * Use:
	 * sudo bpftrace -e 'kprobe:*_fallocate { @[probe] = count() }'
	 *
	 * tracing fallocate(2)
	 */
	fallocate(fd, 0, 0, 1024);

	close(fd);

	return 0;
}
