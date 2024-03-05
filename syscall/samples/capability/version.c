#include <stdio.h>
#include <string.h>
#include <sys/capability.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int ret;
	struct __user_cap_header_struct cap_header;

	ret = capget(&cap_header, NULL);
	if (ret < 0) {
		fprintf(stderr, "capget error: %s", strerror(errno));
	}

	switch(cap_header.version) {
	case _LINUX_CAPABILITY_VERSION_1:
		printf("cap version 1: 0x%x\n", cap_header.version);
		break;
	case _LINUX_CAPABILITY_VERSION_2:
		printf("cap version 2: 0x%x\n", cap_header.version);
		break;
	case _LINUX_CAPABILITY_VERSION_3:
		printf("cap version 3: 0x%x\n", cap_header.version);
		break;
	default:
		printf("unknown version: 0x%x\n", cap_header.version);
		break;
	}

	exit(EXIT_SUCCESS);
}
