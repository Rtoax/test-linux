#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <sys/socket.h>

#include "iovec_helpers.h"

#define UNSOCKET_PATH   "/tmp/fd-pass.socket"
#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while(0)

int main(int argc, char *argv[])
{
	int i;
	ssize_t nbytes;
	char buffer[256];
	int sfd, cfd, fd;
	struct sockaddr_un addr;

	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sfd == -1)
		handle_error("Failed to create socket");

	if (unlink(UNSOCKET_PATH) == -1 && errno != ENOENT)
		handle_error("Removing socket file failed");

	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, UNSOCKET_PATH, sizeof(addr.sun_path)-1);

	if (bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
		handle_error("Failed to bind to socket");

	if (listen(sfd, 5) == -1)
		handle_error("Failed to listen on socket");

	cfd = accept(sfd, NULL, NULL);
	if (cfd == -1)
		handle_error("Failed to accept incoming connection");

	sock_recv_fds(cfd, &fd, 1);

	for (i = 0; i < 1; ++i) {
		fprintf (stdout, "Reading from passed fd %d\n", fd);
		while ((nbytes = read(fd, buffer, sizeof(buffer))) > 0)
			write(1, buffer, nbytes);
		*buffer = '\0';
	}

	close(fd);
	close(cfd);

	return 0;
}
