#include <stdio.h>
#include <netdb.h>
#include "helpers.h"

static void __name(char *name, char *proto)
{
	struct servent *ser;
	ser = getservbyname(name, proto);
	if (ser) {
		print_servent(ser);
	} else {
		printf("there is no such a service\n");
	}
}

int main(void)
{
	__name("ftp", "tcp");
	__name("http", "tcp");
	return 0;
}
