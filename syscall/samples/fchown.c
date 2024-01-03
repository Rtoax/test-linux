#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>		/*S_IRUSR */

int main(int argc, char *argv[])
{
	int fd = open(argv[1], O_RDONLY);
	fchown(fd, S_ISUID, S_ISGID);
	close(fd);
	return 0;
}
