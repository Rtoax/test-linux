#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
	int fd = open("/home/", O_RDONLY);
	fchdir(fd);
	printf("%s\n", (char *)getcwd(NULL, 100));
	close(fd);
	return 0;
}
