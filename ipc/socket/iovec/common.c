#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <sys/socket.h>

#include "common.h"


int recv_fd(int socket, int *fds, int n)
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

	if (recvmsg(socket, &msg, 0) < 0)
		handle_error("Failed to receive message");

	cmsg = CMSG_FIRSTHDR(&msg);

	memcpy(fds, (int *)CMSG_DATA(cmsg), n * sizeof(int));

	return 0;
}

int send_fd(int socket, int *fds, int n)
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

	memcpy((int *)CMSG_DATA(cmsg), fds, n * sizeof(int));

	if (sendmsg(socket, &msg, 0) < 0)
		handle_error("Failed to send message");

	return 0;
}
