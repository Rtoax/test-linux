#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int fd = open("/dev/tty", O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "open /dev/tty failed, %m\n");
		exit(EXIT_FAILURE);
	}

	while (1) {
		char ch;
		int n = read(fd, &ch, 1);
		if (n != 1)
			continue;
		printf("ch %c %d\n", ch, ch);
	}

	close(fd);
	return 0;
}
