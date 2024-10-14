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

	read(d1, buf, sizeof(buf));
	printf("buf = %s\n", buf);
	printf("cur = %ld\n", lseek(d1, 64, SEEK_CUR));
	printf("end = %ld\n", lseek(d1, 0, SEEK_END));

	read(d2, buf, sizeof(buf));
	printf("buf = %s\n", buf);

	close(d1);
	close(d2);

	return 0;
}
