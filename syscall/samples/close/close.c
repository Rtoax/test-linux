#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syscall.h>

int sys_close(unsigned int fd)
{
	return syscall(__NR_close, fd);
}

int main(void)
{
	close(1);
	fprintf(stdout, "Hello\n");
	assert(errno == EBADF);
	perror("fprintf");
	return 0;
}
