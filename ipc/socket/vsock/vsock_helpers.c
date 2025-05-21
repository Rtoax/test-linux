#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/vm_sockets.h>

#include "vsock_helpers.h"


char *vsock_cid_name(unsigned int cid)
{
	switch (cid) {
	case VMADDR_CID_ANY: return "VMADDR_CID_ANY";
	case VMADDR_CID_HOST: return "VMADDR_CID_HOST";
	case VMADDR_CID_LOCAL: return "VMADDR_CID_LOCAL";
	default: return "NUM";
	}
}

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

unsigned int vsock_get_cid_from_args(int argc, char *argv[])
{
	unsigned int cid = 0, i;

	for (i = 0; i < argc; i++) {
		if (!strncmp(argv[i], "cid=", 4)) {
			char *s_cid = argv[i] + 4;
			if (!strcasecmp(s_cid, "any"))
				cid = VMADDR_CID_ANY;
			else if (!strcasecmp(s_cid, "host"))
				cid = VMADDR_CID_HOST;
			else if (!strcasecmp(s_cid, "local"))
				cid = VMADDR_CID_LOCAL;
			else
				cid = atoi(s_cid);
		}
	}

	if (cid) {
#ifdef DEBUG
		fprintf(stderr, "cid=%d\n", cid);
#endif
		return cid;
	}

	fprintf(stderr, "usage: cid=[any|host|local|<NUM>]\n");

	/* not found cid= */
	errno = -ENOENT;
	return 0;
}
