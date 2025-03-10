#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "helpers.h"

int main(void)
{
	struct stat buf;

	int fp = open("/etc/os-release", O_RDONLY);

	fstat(fp, &buf);
	print_stat(&buf);

	sys_fstat(fp, &buf);
	print_stat(&buf);

	return 0;
}
