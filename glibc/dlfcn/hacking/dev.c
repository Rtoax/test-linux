#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

#include "libdev.h"


int main(void)
{
	int totalmem = dev_gettotalmemsize();
	printf("Total memory of device is %d\n", totalmem);
	return 0;
}

