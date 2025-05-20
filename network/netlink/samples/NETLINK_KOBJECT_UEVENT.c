#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <unistd.h>

int main(void)
{
	int fd = socket(AF_NETLINK, SOCK_DGRAM | SOCK_CLOEXEC,
			NETLINK_KOBJECT_UEVENT);
	if (fd == -1) {
		perror("socket");
		exit(1);
	}
	close(fd);

	return 0;
}
