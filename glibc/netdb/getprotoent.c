#include <stdio.h>
#include <netdb.h>
#include "netdb_helpers.h"

int main(void)
{
	struct protoent *pro;

	setprotoent(1);

	while ((pro = getprotoent())) {
		print_protoent(pro);
	}

	endprotoent();

	return 1;
}
