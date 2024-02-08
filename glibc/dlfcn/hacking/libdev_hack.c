#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libdev.h"



static struct device dev = {
	.totalmemsize = 1024,
};


int dev_gettotalmemsize(void)
{
	return dev.totalmemsize;
}

