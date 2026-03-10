#include <stdio.h>
#include <sys/socket.h>

#include "libc.h"

int main(void)
{
	int fd;

	fd = socket(1, 1, 1);
	perror("socket");

	libc_override_set(true);

	fd |= socket(1, 1, 1);
	perror("socket");


	return fd > 0 ? 0 : -1;
}
