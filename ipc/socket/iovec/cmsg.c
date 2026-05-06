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

	printf("size of msghdr %ld\n", sizeof(struct msghdr));
	printf("size of cmsghdr %ld\n", sizeof(struct cmsghdr));

	printf("CMSG_SPACE(0) = %ld\n", CMSG_SPACE(0));
	printf("CMSG_SPACE(1) = %ld\n", CMSG_SPACE(1));
	printf("CMSG_SPACE(20) = %ld\n", CMSG_SPACE(20));

	printf("CMSG_ALIGN(0) = %ld\n", CMSG_ALIGN(0));
	printf("CMSG_ALIGN(1) = %ld\n", CMSG_ALIGN(1));
	printf("CMSG_ALIGN(20) = %ld\n", CMSG_ALIGN(20));

	printf("CMSG_LEN(0) = %ld\n", CMSG_LEN(0));
	printf("CMSG_LEN(1) = %ld\n", CMSG_LEN(1));
	printf("CMSG_LEN(20) = %ld\n", CMSG_LEN(20));

	return 0;
}
