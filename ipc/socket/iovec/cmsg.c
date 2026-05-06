#include <stdio.h>
#include <sys/socket.h>

int main(void)
{
	struct msghdr msg = {
		.msg_iov = NULL,
		.msg_iovlen = 1,
		.msg_control = NULL,
		.msg_controllen = 0,
	};
	(void)msg;

	printf("CMSG_SPACE(0) = %ld\n", CMSG_SPACE(0));
	printf("CMSG_SPACE(1) = %ld\n", CMSG_SPACE(1));
	printf("CMSG_SPACE(20) = %ld\n", CMSG_SPACE(20));

	return 0;
}
