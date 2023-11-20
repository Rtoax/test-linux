#include <stdio.h>
#include <unistd.h>
#include <string.h>


const char *confstr_unsafe(int conf)
{
	int ret;
	size_t len = confstr(conf, NULL, 0);
	static char buffer[256];

	memset(buffer, 0, sizeof(buffer));
	ret = confstr(conf, buffer, len + 1);
	if (ret == 0)
		return "Unknown";
	return buffer;
}

int main(void)
{
#define SYSCONF(c) printf("%-48s %-8d %-8ld %s\n", #c, c, sysconf(c), confstr_unsafe(c));
#include "confs_def.h"
#undef SYSCONF
	return 0;
}
