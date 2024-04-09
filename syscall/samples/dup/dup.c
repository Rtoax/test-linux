#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(void)
{
	int fd = open("a.txt", O_RDWR | O_CREAT, 0644);
	if (fd == -1) {
		perror("open");
		exit(1);
	}

	printf("file open fd = %d\n", fd);

	int ret = dup(fd);
	if (ret == -1) {
		perror("dup");
		exit(1);
	}

	printf("dup fd = %d\n", ret);

	char *buf = "hello";
	char *buf1 = " world\n";

	write(fd, buf, strlen(buf));
	write(ret, buf1, strlen(buf1));

	close(fd);
	return 0;
}
