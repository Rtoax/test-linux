#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


int main(int argc, char *argv[])
{
	struct stat buf;
	const char *filename = "/etc/os-release";

	stat(filename, &buf);

	printf("mode: %x\n", buf.st_mode);
	printf("ino: %ld\n", buf.st_ino);

	if (buf.st_mode & S_IWUSR)
		printf("Owning user can write `%s'.\n", filename);

	return 0;
}
