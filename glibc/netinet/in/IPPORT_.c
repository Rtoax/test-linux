#include <stdio.h>
#include <netinet/in.h>

int main(void)
{
	printf("IPPORT_RESERVED(port mac number) = %d\n", IPPORT_RESERVED);
	printf("IPPORT_USERRESERVED = %d\n", IPPORT_USERRESERVED);

	return 0;
}
