#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

#include "libdev.h"


int main(void)
{
	int totalmem = dev_gettotalmemsize();
	int allocatedmem = dev_getallocatedsize();
	printf("Memory usage %d/%d\n", allocatedmem, totalmem);
	return 0;
}

