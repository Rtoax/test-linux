#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "stat_helpers.h"

int main(void)
{
	struct stat buf;
	const char *file = "/etc/os-release";

	lstat(file, &buf);
	print_stat(file, &buf);
	sys_lstat(file, &buf);
	print_stat(file, &buf);

	return 0;
}
