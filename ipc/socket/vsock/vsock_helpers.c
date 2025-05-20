#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/vm_sockets.h>

#include "vsock_helpers.h"


int vsock_get_local_cid(void)
{
	unsigned int cid;
	int fd, err;

	fd = open(DEV_VSOCK, O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "open(%s) failed, %m\n", DEV_VSOCK);
		return -1;
	}

	err = ioctl(fd, IOCTL_VM_SOCKETS_GET_LOCAL_CID, &cid);
	if (err == -1) {
		fprintf(stderr, "ioctl(%s) failed, %m\n", DEV_VSOCK);
		return -1;
	}

	close(fd);
	return cid;
}
