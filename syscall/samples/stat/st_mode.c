#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	struct stat buf;

	stat("/etc/os-release", &buf);

	printf("mode: %d\n", buf.st_mode);
	printf("ino: %ld\n", buf.st_ino);

	printf("type:S_ISDIR:%d\n", S_ISDIR(buf.st_mode));
	printf("type:S_ISCHR:%d\n", S_ISCHR(buf.st_mode));
	printf("type:S_ISBLK:%d\n", S_ISBLK(buf.st_mode));
	printf("type:S_ISREG:%d\n", S_ISREG(buf.st_mode));
	printf("type:S_ISLNK:%d\n", S_ISLNK(buf.st_mode));
	printf("type:S_ISSOCK:%d\n", S_ISSOCK(buf.st_mode));
	printf("type:S_IFMT:%d\n", S_IFMT);

	printf("type:S_TYPEISMQ:%d\n", S_TYPEISMQ(&buf));
	printf("type:S_TYPEISSEM:%d\n", S_TYPEISSEM(&buf));
	printf("type:S_TYPEISSHM:%d\n", S_TYPEISSHM(&buf));

	return 0;
}
