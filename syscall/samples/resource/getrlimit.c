#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "helpers.h"


int main(void)
{
	int ret;
	struct rlimit rlimit;

	ret = getrlimit(RLIMIT_CORE, &rlimit);
	if (ret != 0) {
		fprintf(stderr, "get RLIMIT_CORE failed.\n");
		return 1;
	}
	/* unlimited(-1) */
	print_rlimit("RLIMIT_CORE", &rlimit);

	getrlimit(RLIMIT_CPU, &rlimit);
	print_rlimit("RLIMIT_CPU", &rlimit);

	getrlimit(RLIMIT_NPROC, &rlimit);
	print_rlimit("RLIMIT_NPROC", &rlimit);

	getrlimit(RLIMIT_NICE, &rlimit);
	print_rlimit("RLIMIT_NICE", &rlimit);

	return 0;
}
