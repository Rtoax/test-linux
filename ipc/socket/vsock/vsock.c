#include <stdio.h>
#include <stdlib.h>

#include "vsock_helpers.h"

int main(int argc, char *argv[])
{
	unsigned int cid;
	cid = vsock_get_local_cid();
	printf("cid = %d\n", cid);
	cid = vsock_get_cid_from_args(argc, argv);
	printf("cid = %d\n", cid);
	return 0;
}
