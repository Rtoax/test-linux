#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libdev.h"



static struct device dev = {
	.totalmemsize = 4096,
	.allocatedsize = 0,
};


int dev_gettotalmemsize(void)
{
	return dev.totalmemsize;
}

int dev_getallocatedsize(void)
{
	return dev.allocatedsize;
}

