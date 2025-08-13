#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <sys/syscall.h>

#include "iovec_helpers.h"

#define UNSOCKET_PATH   "/tmp/fd-pass.socket"
#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while(0)

int main(int argc, char *argv[])
{
	int sfd, fd;
	struct sockaddr_un addr;

	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sfd == -1)
		handle_error("Failed to create socket");

	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, UNSOCKET_PATH, sizeof(addr.sun_path)-1);

#ifdef MEMFD
	const int size = 0xff;
	fd = syscall(SYS_memfd_create, "shma", 0);
	if (fd < 0)
		handle_error("SYS_memfd_create error.");

	ftruncate(fd, size);

	void *ptr0 = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	memset(ptr0, 'R', size);
	munmap(ptr0, size);
#else
	fd = open("/etc/os-release", O_RDONLY);
	if (fd < 0)
		handle_error("Failed to open file 1 for reading");
	else
		fprintf (stdout, "Opened fd %d in parent\n", fd);
#endif

	if (connect(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1)
		handle_error("Failed to connect to socket");

	sock_send_fds(sfd, &fd, 1);

	close(fd);
	close(sfd);
	exit(EXIT_SUCCESS);
}
