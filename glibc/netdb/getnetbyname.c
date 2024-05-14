#include <netdb.h>
#include <stdio.h>
#include "helpers.h"

int main(void)
{
	struct netent *net = getnetbyname("default");

	print_netent(net);

	return 0;
}
