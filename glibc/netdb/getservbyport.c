#include <stdio.h>
#include <netdb.h>
#include "helpers.h"

static void __port_tcp(int port, char *proto)
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
	__port_tcp(htons(23), "tcp");
	__port_tcp(htons(80), "tcp");
	return 0;
}
