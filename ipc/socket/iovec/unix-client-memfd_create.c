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


int main(int argc, char *argv[])
{
	int sfd, fds[2];
	struct sockaddr_un addr;
	const int size = 0xff;
	void *ptr0;

	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sfd == -1)
		handle_error("Failed to create socket");

	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, UNSOCKET_PATH, sizeof(addr.sun_path)-1);

	fds[0] = syscall(SYS_memfd_create, "shma", 0);
	if (fds[0] < 0)
		handle_error("SYS_memfd_create error.");

	ftruncate(fds[0], size);

	ptr0 = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fds[0], 0);
	memset(ptr0, 'R', size);
	munmap(ptr0, size);

	if (connect(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
		handle_error("Failed to connect to socket");

	sock_send_fds(sfd, fds, 1);

	exit(EXIT_SUCCESS);
}
