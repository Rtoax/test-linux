#pragma once

struct device {
	int totalmemsize;
	int allocatedsize;
};

char *dev_malloc(size_t size);
int dev_gettotalmemsize(void);
int dev_getallocatedsize(void);

