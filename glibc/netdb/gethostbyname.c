/**
 * struct hostent *gethostbyname(const char *name);
 * struct hostent *gethostbyname2(const char *name, int af);
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
	const char name[] = "www.baidu.com";

	host = gethostbyname(name);
	if (!host) {
		perror("gethostbyname() error!");
		exit(1);
	}
	print_hostent(host);

	host = gethostbyname2(name, AF_INET);
	if (!host) {
		perror("gethostbyname2() error!");
		exit(1);
	}
	print_hostent(host);

	return 0;
}
