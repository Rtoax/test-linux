#include <stdio.h>
#include <sys/socket.h>


int main(void)
{
	int fd = socket(1, 1, 1);
	perror("socket");
	return fd > 0 ? 0 : -1;
}
