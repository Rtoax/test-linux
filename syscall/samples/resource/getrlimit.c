#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "helpers.h"


int main(void)
{
	int __attribute__((unused)) ret;
	struct rlimit rlimit;

	ret = getrlimit(RLIMIT_CORE, &rlimit);
	if (ret != 0) {
		fprintf(stderr, "get RLIMIT_CORE failed.\n");
		return 1;
	}
	/* unlimited(-1) */
	print_rlimit("RLIMIT_CORE", &rlimit);

	return 0;
}
