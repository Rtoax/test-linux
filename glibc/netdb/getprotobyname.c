#include <stdio.h>
#include <netdb.h>
#include "netdb_helpers.h"

int main(void)
{
	struct protoent *pro;

	pro = getprotobyname("TCP");
	print_protoent(pro);

	pro = getprotobyname("UDP");
	print_protoent(pro);

	pro = getprotobyname("icmp");
	print_protoent(pro);

	return 0;
}
