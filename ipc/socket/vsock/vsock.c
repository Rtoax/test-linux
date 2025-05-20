#include <stdio.h>
#include <stdlib.h>

#include "vsock_helpers.h"

int main(void)
{
	unsigned int cid;
	cid = vsock_get_local_cid();
	printf("cid = %d\n", cid);
	return 0;
}
