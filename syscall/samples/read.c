#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int read_off(int fd, off_t off, void *buf, size_t size, int keepoff)
{
	off_t cur_pos;
	int err, n;

	cur_pos = lseek(fd, 0, SEEK_CUR);

	err = lseek(fd, off, SEEK_SET);
	if (err == (off_t)-1) {
		perror("lseek");
		return -errno;
	}
	n = read(fd, buf, size);

	if (keepoff)
		lseek(fd, cur_pos, SEEK_SET);
	return n;
}

int main(void)
{
	ssize_t n;
	char buf[64];

	while (1) {
		n = read(0, buf, sizeof(buf));
		if (n == -1) {
			fprintf(stderr, "%m\n");
			continue;
		}
		printf("%c", buf[0]);
	}

	return 0;
}
