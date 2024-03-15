#include <stdio.h>
#include <unistd.h>

int main(void)
{
	const char *path = "./";

#define PATH_CONF(pc) printf(" pathconf: %-32s %ld\n", #pc, pathconf(path, _PC_LINK_MAX));
	#include "pathconf.h"
#undef PATH_CONF

#define PATH_CONF(pc) printf("fpathconf: %-32s %ld\n", #pc, fpathconf(fileno(stdin), _PC_LINK_MAX));
	#include "pathconf.h"
#undef PATH_CONF

	return 0;
}
