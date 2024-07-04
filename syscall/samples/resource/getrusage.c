#include <stdio.h>
#include <sys/resource.h>

#include "helpers.h"

int main(void)
{
	struct rusage rusage;

	getrusage(RUSAGE_SELF, &rusage);
	print_rusage(&rusage);

	return 0;
}

