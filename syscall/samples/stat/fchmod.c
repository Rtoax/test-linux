#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	mkdir("rong.out", 0777);

	int fd = open("rong.out", O_RDONLY);

	fchmod(fd, 04244);

	return 0;
}
