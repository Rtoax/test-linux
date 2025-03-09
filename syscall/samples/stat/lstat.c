#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "helpers.h"

int main(void)
{
	struct stat buf;

	lstat("/etc/os-release", &buf);
	print_stat(&buf);
	sys_lstat("/etc/os-release", &buf);
	print_stat(&buf);

	return 0;
}
