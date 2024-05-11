#include <stdio.h>
#include <netdb.h>

int main(void)
{
	struct servent *serv;

	setservent(1);

	while ((serv = getservent())) {
		printf("----\n");
		printf("name:		%s\n", serv->s_name);
		printf("aliases:	%s\n", serv->s_aliases[0]);
		printf("port:		%d\n", serv->s_port);
		printf("ntohs(prot):%d\n", ntohs(serv->s_port));
		printf("proto:		%s\n", serv->s_proto);
	}

	endservent();
	return 0;
}
