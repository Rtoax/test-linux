#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "helpers.h"


int main(int argc, char *argv[])
{
	struct stat buf;
	const char *filename = "/etc/os-release";

	if (argc > 1)
		filename = argv[1];

	stat(filename, &buf);

	print_stat(filename, &buf);

	return 0;
}
