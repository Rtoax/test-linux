/**
 * Tests:
 * - commit 84ad22e4987e ("ioctl: test BLKZEROOUT")
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>

int main(int argc, char *argv[])
{
	int err, fd;
	unsigned long long range[2] = {0, 0};
	char *dev;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s [dev]\n", argv[0]);
		exit(1);
	}

	dev = argv[1];

	fd = open(dev, O_RDWR);
	if (fd == -1) {
		fprintf(stderr, "open(%s) %m\n", dev);
		exit(1);
	}

	/**
	 * Get number of 512B blocks
	 */
	err = ioctl(fd, BLKGETSIZE, &range[1]);
	if (err == -1) {
		fprintf(stderr, "ioctl(%s, BLKGETSIZE): %m\n", dev);
	}

	printf("device %s size %lld GB\n", dev, range[1] * 512 / 1024 / 1024 / 1024);

	err = ioctl(fd, BLKZEROOUT, range);
	if (err == -1) {
		fprintf(stderr, "ioctl(%s, BLKZEROOUT): %m\n", dev);
	}

	close(fd);
	return 0;
}
