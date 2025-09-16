/**
 * struct hostent *gethostbyaddr(const void addr[.len],
 *                               socklen_t len, int type);
 *
 * int gethostbyaddr_r(const void addr[restrict .len], socklen_t len,
 *                     int type,
 *                     struct hostent *restrict ret,
 *                     char buf[restrict .buflen], size_t buflen,
 *                     struct hostent **restrict result,
 *                     int *restrict h_errnop);
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
	struct hostent *host, hostbuf;
	char ip[] = "127.0.0.1";
	struct in_addr addr;
	socklen_t sklen;
	char buffer[1024];
	int err;

	sklen = sizeof(addr);
	inet_pton(AF_INET, ip, &addr);

	host = gethostbyaddr(&addr, sklen, AF_INET);
	if (!host) {
		perror("gethostbyaddr() error!");
		exit(1);
	}
	print_hostent(host);

	gethostbyaddr_r(&addr, sklen, AF_INET, &hostbuf, buffer, sizeof(buffer),
			&host, &err);
	print_hostent(host);

	return 0;
}
