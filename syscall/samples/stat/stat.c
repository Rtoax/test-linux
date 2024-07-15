#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "helpers.h"


int main(int argc, char *argv[])
{
	struct stat buf;
	const char *filename = "/etc/os-release";

	stat(filename, &buf);

	print_stat(&buf);

	return 0;
}
