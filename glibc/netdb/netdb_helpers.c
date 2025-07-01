// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include "netdb_helpers.h"


int print_netent(struct netent *net)
{
	printf("netent: n_name: %s\n", net->n_name);
	printf("netent: n_aliases[0]: %s\n", net->n_aliases[0]);
	printf("netent: n_addrtype: %d\n", net->n_addrtype);
#if defined(__sw_64__)
# define F_N_NET "%ld"
#else
# define F_N_NET "%d"
#endif
	printf("netent: n_net: "F_N_NET"\n", net->n_net);
	return 0;
}

int print_hostent(struct hostent *host)
{
	int i;
	struct sockaddr_in addr_in;
	struct in_addr in;

	if (!host)
		return -1;

	printf("Domain name: %s \n", host->h_name);
	for (i = 0; host->h_aliases[i]; i++) {
		printf("Aliases %d: %s\n", i + 1, host->h_aliases[i]);
	}
	printf("Address type: %s \n", host->h_addrtype == AF_INET ? "AF_INET" : "AF_INET6");
	for (i = 0; host->h_addr_list[i]; i++) {
		printf("IP address %d: %s \n", i + 1, inet_ntoa(*(struct in_addr *)host->h_addr_list[i]));
	}

	memcpy(&addr_in.sin_addr.s_addr, host->h_addr, 4);
	in.s_addr = addr_in.sin_addr.s_addr;
	printf("IP: %s\n", inet_ntoa(in));

	return 0;
}

int print_servent(struct servent *ser)
{
	printf("name:  %s\n", ser->s_name);
	printf("port:  %d\n", ntohs(ser->s_port));
	printf("proto: %s\n", ser->s_proto);
	printf("alias: %s\n", ser->s_aliases[0]);
	return 0;
}

int print_protoent(struct protoent *pro)
{
	printf("name:   %s\n", pro->p_name);
	printf("number: %d\n", pro->p_proto);
	printf("alias:  %s\n", pro->p_aliases[0]);
#if 0
	printf("alias:  %s\n", pro->p_aliases[1]);
	printf("alias:  %s\n", pro->p_aliases[2]);
#endif
	return 0;
}
