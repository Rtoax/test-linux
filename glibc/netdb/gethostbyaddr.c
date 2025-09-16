/**
 * struct hostent *gethostbyaddr(const void addr[.len],
 *                               socklen_t len, int type);
 */
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
	char ip[] = "127.0.0.1";
	struct in_addr addr;
	socklen_t sklen;

	sklen = sizeof(addr);
	inet_pton(AF_INET, ip, &addr);

	host = gethostbyaddr(&addr, sklen, AF_INET);
	if (!host) {
		perror("gethostbyaddr() error!");
		exit(1);
	}

	print_hostent(host);

	return 0;
}
