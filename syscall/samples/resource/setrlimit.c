#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/resource.h>

int main(void)
{
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

	return 0;
}
