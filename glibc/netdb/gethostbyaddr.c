#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int i;
	struct hostent *host;
	char ip[] = "127.0.0.1";

	host = gethostbyaddr(ip, sizeof(ip), AF_INET);
	if (!host) {
		perror("gethostbyaddr() error!");
		exit(1);
	}

	printf("Domain name: %s \n", host->h_name);
	for (i = 0; host->h_aliases[i]; i++) {
		printf("Aliases %d: %s\n", i + 1, host->h_aliases[i]);
	}
	printf("Address type: %s \n", host->h_addrtype == AF_INET? "AF_INET":"AF_INET6");
	for (i = 0; host->h_addr_list[i]; i++) {
		printf("IP address %d: %s \n", i + 1, inet_ntoa(*(struct in_addr *)host->h_addr_list[i]));
	}

	return 0;
}
