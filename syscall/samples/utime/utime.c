#include <stdio.h>
#include <time.h>
#include <utime.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	int ret;
	char *filename;
	struct utimbuf utim;

	filename = "a.txt";

	utim.actime = 12;
	utim.modtime = 13;

	ret = utime(filename, &utim);
	if (ret == -1) {
		fprintf(stderr, "utime(%s) %m\n", filename);
		return 0;
	}

	return 0;
}
