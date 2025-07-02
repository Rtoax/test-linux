#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "stat_helpers.h"


int main(int argc, char *argv[])
{
	struct stat buf;
	const char *filename = "/etc/os-release";

	if (argc > 1)
		filename = argv[1];

	printf("size of struct stat %ld\n", sizeof(struct stat));
	printf("offset of st_size %ld\n", offsetof(struct stat, st_size));

	stat(filename, &buf);

	print_stat(filename, &buf);

	return 0;
}
