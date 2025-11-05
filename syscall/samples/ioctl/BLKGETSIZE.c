#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>

int main(void)
{
	int err;
	int fd = open("/etc/os-release", O_RDONLY);
	unsigned long long range[2] = {0, 0};

	err = ioctl(fd, BLKGETSIZE, &range[1]);
	if (err == -1) {
		fprintf(stderr, "ioctl(): %m\n");
	}

	close(fd);
	return 0;
}
