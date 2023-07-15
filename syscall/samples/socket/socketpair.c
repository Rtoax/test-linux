#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
	int nbytes;
	int socket_pair[2];
	pid_t pid;


	if (socketpair(AF_UNIX, SOCK_STREAM | SOCK_SEQPACKET, 0, socket_pair) == -1 ) {
		printf("Error, socketpair create failed, errno(%d): %s\n",
			errno, strerror(errno));
		return EXIT_FAILURE;
	}

	pid = fork();

	if (pid > 0) {

		int i;
		const char* msg = "SOCKET PAIR TEST.";

		close(socket_pair[1]);

		for (i = 0; i < 2; i++) {
			write(socket_pair[0], msg, strlen(msg));
			printf("Parent: write success, pid: %d\n", getpid());
			sleep(1);
		}

		printf("Parent: close fd.\n");
		close(socket_pair[0]);

		waitpid(pid, 0, 0);

	} else if (pid == 0) {

		char buf[128] = {0};

		close(socket_pair[0]);

		while (true) {
			nbytes = read(socket_pair[1], buf, sizeof(buf));
			if (nbytes == 0) {
				printf("Child: read end of file.\n");
				break;
			} else if (nbytes > 0) {
				printf("Child: read result: %s, pid: %d\n",buf, getpid());
			} else {
				printf("Child: read failed: %s.\n", strerror(errno));
				break;
			}
		}
	} else if (pid < 0) {

		printf("Error, fork failed, errno(%d): %s\n", errno, strerror(errno));
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
