#include <stdio.h>
#include <netdb.h>
#include "netdb_helpers.h"

static void __port(int port, char *proto)
{
	struct servent *ser;
	ser = getservbyport(port, proto);
	if (ser) {
		print_servent(ser);
	} else {
		printf("there is no such a service\n");
	}
}

int main(void)
{
	__port(htons(22), "tcp");
	__port(htons(23), "tcp");
	__port(htons(80), "tcp");
	__port(htons(8080), "tcp");
	return 0;
}
