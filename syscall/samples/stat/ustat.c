#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "stat_helpers.h"


int main(int argc, char *argv[])
{
	int ret;
	struct tl_ustat ubuf;
	dev_t dev = 1;

	ret = sys_ustat(dev, &ubuf);
	fprintf(stderr, "ustat return %d\n", ret);

	print_ustat(&ubuf);

	return 0;
}
