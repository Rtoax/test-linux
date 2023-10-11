#define _GNU_SOURCE         /* See feature_test_macros(7) */
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

#include "common.h"

static void send_fd(int socket, int *fds, int n)
{
    struct msghdr msg = {0};
    struct cmsghdr *cmsg;
    char buf[CMSG_SPACE(n * sizeof(int))], dup[256];
    memset(buf, '\0', sizeof(buf));
    struct iovec io = { .iov_base = &dup, .iov_len = sizeof(dup) };

    msg.msg_iov = &io;
    msg.msg_iovlen = 1;
    msg.msg_control = buf;
    msg.msg_controllen = sizeof(buf);

    cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;   /* Transfer file descriptors.  */
    cmsg->cmsg_len = CMSG_LEN(n * sizeof(int));

    memcpy((int *)CMSG_DATA(cmsg), fds, n * sizeof (int));

    if (sendmsg(socket, &msg, 0) < 0)
        handle_error("Failed to send message");
}

int main(int argc, char *argv[])
{
    int sfd, fds[2];
    struct sockaddr_un addr;

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1)
        handle_error("Failed to create socket");

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, UNSOCKET_PATH, sizeof(addr.sun_path)-1);

    const int size = 0xff;
	fds[0] = syscall(SYS_memfd_create, "shma", 0);
	if (fds[0] < 0)
		handle_error("SYS_memfd_create error.");
	ftruncate(fds[0], size);
	void *ptr0 = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fds[0], 0);
	memset(ptr0, 'R', size);
	munmap(ptr0, size);

    if (connect(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
        handle_error("Failed to connect to socket");

    send_fd(sfd, fds, 1);

    exit(EXIT_SUCCESS);
}
