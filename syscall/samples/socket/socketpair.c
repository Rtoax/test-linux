#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/wait.h>


const char* str = "SOCKET PAIR TEST.";

int main(int argc, char* argv[])
{
	int socket_pair[2];
	pid_t pid;

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, socket_pair) == -1 ) {
		printf("Error, socketpair create failed, errno(%d): %s\n",
			errno, strerror(errno));
		return EXIT_FAILURE;
	}

	pid = fork();

	if(pid > 0) {

		close(socket_pair[1]);

		write(socket_pair[0], str, strlen(str));

		printf("Parent: write success, pid: %d\n", getpid());
		waitpid(pid, 0, 0);

	} else if(pid == 0) {

		char buf[128] = {0};

		close(socket_pair[0]);
		read(socket_pair[1], buf, sizeof(buf));
		printf("Child: read result: %s, pid: %d\n",buf, getpid());

	} else if (pid < 0) {

		printf("Error, fork failed, errno(%d): %s\n", errno, strerror(errno));
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
