#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

int main(void)
{
	struct sockaddr	addr;
	addr.sa_family = AF_LOCAL;

	bind(1, &addr, sizeof(struct sockaddr));
	perror("bind");
	return 0;
}
