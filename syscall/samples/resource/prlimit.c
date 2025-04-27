#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "resource_helpers.h"


int main(void)
{
	int ret;
	struct rlimit rlimit;
	pid_t pid = getpid();

	ret = prlimit(pid, RLIMIT_NOFILE, NULL, &rlimit);
	if (ret != 0) {
		fprintf(stderr, "get RLIMIT_NOFILE failed.\n");
		return 1;
	}

	print_rlimit("RLIMIT_NOFILE", &rlimit);

	return 0;
}
