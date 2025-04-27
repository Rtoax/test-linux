#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

#include "netdb_helpers.h"


int main(int argc, char* argv[])
{
	struct hostent *host;
	char name[] = "www.baidu.com";

	host = gethostbyname(name);
	if (!host) {
		perror("gethostbyname() error!");
		exit(1);
	}

	print_hostent(host);

	return 0;
}
