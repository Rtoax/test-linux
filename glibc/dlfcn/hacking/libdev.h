#pragma once

struct device {
	int totalmemsize;
	int allocatedsize;
};

int dev_gettotalmemsize(void);
int dev_getallocatedsize(void);

