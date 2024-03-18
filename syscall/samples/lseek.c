#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[])
{
	int d1, d2;
	char buf[32];
	char *file = "/etc/os-release";

	d1 = open(file, O_RDONLY);
	d2 = open(file, O_RDONLY);

	lseek(d1, 64, SEEK_SET);

	read(d2, buf, sizeof(buf));
	printf("buf = %s\n", buf);

	return 0;
}
