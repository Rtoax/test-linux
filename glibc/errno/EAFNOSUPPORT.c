#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	int sockfd;
	sockfd = socket(0xffffffff/* not exist */, SOCK_STREAM, 0);
	assert(errno == EAFNOSUPPORT);
	perror("socket");
	return 0;
}
