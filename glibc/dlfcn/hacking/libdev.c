#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libdev.h"



static struct device dev = {
	.totalmemsize = 4096,
};


int dev_gettotalmemsize(void)
{
	return dev.totalmemsize;
}

