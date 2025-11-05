#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>

int main(void)
{
	int err, fd;
	unsigned long long range[2] = {0, 0};
	char *dev = "/dev/sda";

	fd = open(dev, O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "open(%s) %m\n", dev);
		exit(1);
	}

	/**
	 * Get number of 512B blocks
	 */
	err = ioctl(fd, BLKGETSIZE, &range[1]);
	if (err == -1) {
		fprintf(stderr, "ioctl(): %m\n");
	}

	printf("device %s size %lld GB\n", dev, range[1] * 512 / 1024 / 1024 / 1024);

	close(fd);
	return 0;
}
