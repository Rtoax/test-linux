#include <stdio.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/socket.h>

#include "iovec_helpers.h"


int main(int argc, const char *argv[])
{
	int pairfd[2];
	int ret = socketpair(PF_UNIX, SOCK_DGRAM, 0, pairfd);
	assert(ret != -1);

	pid_t pid = fork();
	assert(pid >= 0);

	if (pid == 0) {
		close(pairfd[0]);
		int fd_to_pass = open("/etc/os-release", O_RDONLY, 0666);
		send_fd(pairfd[1], &fd_to_pass, 1);
		close(fd_to_pass);
	} else if (pid > 0) {
		close(pairfd[1]);
		char buf[1024];
		int FD;
		recv_fd(pairfd[0], &FD, 1);
		read(FD, buf, sizeof(buf));
		printf("[Parent] I got fd %d and data %s\n", FD, buf);
		close(FD);
	}
	return 0;
}
