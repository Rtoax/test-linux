#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "helpers.h"

int main(int argc, char *argv[])
{
	struct stat buf;
	char *file = "/etc/os-release";

	if (argc > 1)
		file = argv[1];

	stat(file, &buf);

	print_stat(file, &buf);

	return 0;
}
