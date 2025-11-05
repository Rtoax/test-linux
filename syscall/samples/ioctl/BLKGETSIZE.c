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
	unsigned int sector_size;
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

	err = ioctl(fd, BLKSSZGET, &sector_size);
	if (err == -1) {
		fprintf(stderr, "ioctl(%s, BLKSSZGET): %m\n", dev);
		goto out;
	}

	err = ioctl(fd, BLKGETSIZE, &range[1]);
	if (err == -1) {
		fprintf(stderr, "ioctl(%s, BLKGETSIZE): %m\n", dev);
		goto out;
	}

	printf("device %s sector size %d, total size %lld GB\n", dev,
		sector_size,
		range[1] * sector_size / 1024 / 1024 / 1024);

	err = ioctl(fd, BLKZEROOUT, range);
	if (err == -1) {
		fprintf(stderr, "ioctl(%s, BLKZEROOUT): %m\n", dev);
	}

out:
	close(fd);
	return 0;
}
