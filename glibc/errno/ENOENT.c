#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>


int main(void)
{
	int fd = open("__not_exist_file__", O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "open %m (%s, %d)\n", strerror(errno), errno);
	}
	return 0;
}
