#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <malloc.h>

int main(void)
{
	struct netent *net;

	setnetent(1);

	while ((net = getnetent())) {
		printf("netent: n_name: %s\n", net->n_name);
		printf("netent: n_aliases[0]: %s\n", net->n_aliases[0]);
		printf("netent: n_addrtype: %d\n", net->n_addrtype);
		printf("netent: n_net: %d\n", net->n_net);
	}

	endnetent();

	return 0;
}
