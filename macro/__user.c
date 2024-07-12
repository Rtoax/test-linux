#include <stdio.h>

#include "unused.h"

#define __user __attribute__((noderef, address_space(1)))

int main(void)
{
	int __unused __user *a;
	return 0;
}
