#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/resource.h>

#include "resource_helpers.h"


int main(void)
{
	pid_t child;
	struct rlimit rlimit;

	getrlimit(RLIMIT_CORE, &rlimit);
	print_rlimit("RLIMIT_CORE", &rlimit);

	rlimit.rlim_cur = rlimit.rlim_max = 1024 * 1024 * 10;
	setrlimit(RLIMIT_CORE, &rlimit);

	getrlimit(RLIMIT_CORE, &rlimit);
	print_rlimit("RLIMIT_CORE setted", &rlimit);

	child = fork();
	if (child == 0) {
		/**
		 * Children will inherit parent's rlimit
		 */
		printf("Child running.\n");
		getrlimit(RLIMIT_CORE, &rlimit);
		print_rlimit("RLIMIT_CORE child", &rlimit);
	} else if (child > 0) {
		printf("Parent running.\n");
		getrlimit(RLIMIT_CORE, &rlimit);
		print_rlimit("RLIMIT_CORE parent", &rlimit);
		wait(NULL);
	}

	return 0;
}
