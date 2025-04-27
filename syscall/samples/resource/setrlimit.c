#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/resource.h>

#include "resource_helpers.h"


void sig_handler(int sig)
{
	switch (sig) {
	case SIGXCPU:
		printf("catch SIGXCPU.\n");
		exit(1);
	}
}

int main(void)
{
	int ret;
	unsigned long i, cnt_success = 0;
	const unsigned long nr_max = 1000000;
	int *fds = NULL;
	struct rlimit rlimit;

	getrlimit(RLIMIT_NOFILE, &rlimit);
	printf("Number open files limit is %ld(%ld)\n",
	       rlimit.rlim_cur, rlimit.rlim_max);

	/* Set max number of open files to rlim_max  */
	rlimit.rlim_cur = rlimit.rlim_max;
	setrlimit(RLIMIT_NOFILE, &rlimit);

	fds = malloc(sizeof(int) * nr_max);
	memset(fds, 0, sizeof(int) * nr_max);

	for (i = 0; i < nr_max; i++) {
		int fd = socket(AF_UNIX, SOCK_STREAM, 0);
		if (fd == -1) {
			perror("socket");
			break;
		} else {
			fds[cnt_success++] = fd;
		}
	}

	printf("The max fd is %d\n", fds[cnt_success - 1]);

	for (i = 0; i < cnt_success; i++) {
		close(fds[i]);
	}

	/* CPU */
	signal(SIGXCPU, sig_handler);

	getrlimit(RLIMIT_CPU, &rlimit);
	print_rlimit("RLIMIT_CPU", &rlimit);

	rlimit.rlim_cur = 1;
	ret = setrlimit(RLIMIT_CPU, &rlimit);
	if (ret == -1) {
		fprintf(stderr, "setrlimit RLIMIT_CPU: %m");
		return -1;
	}
	/* Trigger SIGXCPU */
	while (1);

	return 0;
}
