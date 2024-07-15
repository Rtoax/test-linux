#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "helpers.h"

int main(int argc, char *argv[])
{
	struct stat buf;

	stat("/etc/os-release", &buf);

	print_stat(&buf);

	return 0;
}
