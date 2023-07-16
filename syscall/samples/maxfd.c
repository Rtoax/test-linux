#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>


int main(void)
{
	unsigned long i, cnt_success = 0;
	const unsigned long nr_max = 1000000;
	int *fds = malloc(sizeof(int) * nr_max);
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
