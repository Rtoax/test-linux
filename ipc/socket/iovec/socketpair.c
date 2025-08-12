#include <stdio.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/socket.h>

static const int CONTROL_LEN = CMSG_LEN(sizeof(int));

void send_fd(int fd, int fd_to_send)
{
	struct iovec iov[1];
	struct msghdr msg;
	struct cmsghdr cm;
	char buf[0];

	iov[0].iov_base	= buf;
	iov[0].iov_len	= 1;
	msg.msg_name	= NULL;
	msg.msg_namelen	= 0;
	msg.msg_iov	= iov;
	msg.msg_iovlen	= 1;

	cm.cmsg_len	= CONTROL_LEN;
	cm.cmsg_level	= SOL_SOCKET;
	cm.cmsg_type	= SCM_RIGHTS;
	*(int *)CMSG_DATA(&cm) = fd_to_send;
	msg.msg_control	= &cm;
	msg.msg_controllen = CONTROL_LEN;

	sendmsg(fd, &msg, 0);
}

int recv_fd(int fd)
{
	struct iovec iov[1];
	struct msghdr msg;
	struct cmsghdr cm;
	char buf[0];

	iov[0].iov_base	= buf;
	iov[0].iov_len	= 1;
	msg.msg_name	= NULL;
	msg.msg_namelen	= 0;
	msg.msg_iov	= iov;
	msg.msg_iovlen	= 1;

	msg.msg_control		= &cm;
	msg.msg_controllen	= CONTROL_LEN;

	recvmsg(fd, &msg, 0);

	return *(int *)CMSG_DATA(&cm);
}

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
		send_fd(pairfd[1], (fd_to_pass > 0) ? fd_to_pass : 0 );
		close(fd_to_pass);
	} else if (pid > 0) {
		close(pairfd[1]);
		char buf[1024];
		int FD = recv_fd(pairfd[0]);
		read(FD, buf, sizeof(buf));
		printf("[Parent] I got fd %d and data %s\n", FD, buf);
		close(FD);
	}
	return 0;
}
