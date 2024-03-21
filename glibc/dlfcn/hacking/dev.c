#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

#include "libdev.h"


int main(void)
{
	int totalmem, allocatedmem;
	totalmem = dev_gettotalmemsize();
	allocatedmem = dev_getallocatedsize();
	printf("Memory usage %d/%d\n", allocatedmem, totalmem);
	dev_malloc(1024);
	allocatedmem = dev_getallocatedsize();
	printf("Memory usage %d/%d\n", allocatedmem, totalmem);
	dev_malloc(1024);
	allocatedmem = dev_getallocatedsize();
	printf("Memory usage %d/%d\n", allocatedmem, totalmem);
	dev_malloc(1024);
	allocatedmem = dev_getallocatedsize();
	printf("Memory usage %d/%d\n", allocatedmem, totalmem);
	return 0;
}

