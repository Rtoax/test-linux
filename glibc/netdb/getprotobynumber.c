#include <stdio.h>
#include <netdb.h>
#include "helpers.h"

int main(void)
{
	struct protoent *pro;

	pro = getprotobynumber(1);
	print_protoent(pro);

	pro = getprotobynumber(17);
	print_protoent(pro);

	pro = getprotobynumber(3);
	print_protoent(pro);

	return 0;
}
