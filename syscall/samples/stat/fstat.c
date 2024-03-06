#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void)
{
	struct stat buf;

	int fp = open("/etc/os-release", O_RDONLY);

	fstat(fp, &buf);

	printf("mode: %d\n", buf.st_mode);
	printf("ino: %ld\n", buf.st_ino);

	return 0;
}
