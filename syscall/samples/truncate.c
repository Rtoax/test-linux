#include <stdio.h>
#include <errno.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	FILE *fp;
	int i, ret, len;
	unsigned char buffer[4] = {'a'};
	const char *file = "tmp.dat";

	fp = fopen(file, "w");

	len = 1024;

	for (i = 0; i < len; i++)
		fwrite(buffer, sizeof(char), 1, fp);

	fclose(fp);

	ret = truncate(file, len / 2);
	if (ret == -1) {
		fprintf(stderr, "truncate %m\n");
		return -errno;
	}

	return 0;
}
