#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <sys/mount.h>


int main(int argc, char *argv[])
{
	int ret;
	const char *source = "fs.ext4";
	const char *target = "tmp-dir/";

	ret = mount(source, target, "ext4", 0, NULL);
	if (ret == -1) {
		fprintf(stderr, "mount: %s\n", strerror(errno));
		exit(1);
	}

	exit(0);
}

