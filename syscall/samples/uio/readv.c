#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/uio.h>


int main(void)
{
	char buf1[3] = {0};
	char buf2[64] = {0};

	struct iovec iov[2];
	iov[0].iov_base = buf1;
	iov[0].iov_len = sizeof(buf1);
	iov[1].iov_base = buf2;
	iov[1].iov_len = sizeof(buf2);

	FILE *fp = fopen("/etc/os-release", "rb");
	int len = readv(fileno(fp), iov, 2);

	printf("Read bytes: %d \n", len);
	printf("First message: %s \n", buf1);
	printf("Second message: %s \n", buf2);

	return 0;
}

