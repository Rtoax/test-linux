#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "libdev.h"

#define DEV_TOTALMEMSIZE	4096

static struct device dev = {
	.totalmemsize = DEV_TOTALMEMSIZE,
	.allocatedsize = 0,
};


char *dev_malloc(size_t size)
{
	if (dev.allocatedsize + size > DEV_TOTALMEMSIZE) {
		fprintf(stderr, "Device out of memory.\n");
		errno = -ENOMEM;
		return NULL;
	}
	errno = 0;
	dev.allocatedsize += size;
	return "Success";
}

int dev_gettotalmemsize(void)
{
	return dev.totalmemsize;
}

int dev_getallocatedsize(void)
{
	return dev.allocatedsize;
}

