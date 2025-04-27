#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <malloc.h>

#include "netdb_helpers.h"

int main(void)
{
	struct netent *net;

	setnetent(1);

	while ((net = getnetent()))
		print_netent(net);

	endnetent();

	return 0;
}
