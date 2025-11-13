#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>


#define SERVER "/tmp/serversocket"
#define MAXMSG 512

int make_named_socket(const char *filename)
{
	struct sockaddr_un name;
	int sock;
	size_t size;

	/* Create the socket. */
	sock = socket(PF_LOCAL, SOCK_DGRAM, 0);
	if (sock < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	/* Bind a name to the socket. */
	name.sun_family = AF_LOCAL;
	strncpy(name.sun_path, filename, sizeof(name.sun_path));
	name.sun_path[sizeof(name.sun_path) - 1] = '\0';
	/**
	 * The size of the address is the oﬀset of the start of the flename,
	 * plus its length, plus one for the terminating null byte.
	 * Alternatively you can just do:
	 * size = SUN LEN(&name);
	 */
	size = (offsetof(struct sockaddr_un, sun_path) + strlen(name.sun_path) + 1);
	if (bind(sock, (struct sockaddr *)&name, size) < 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
	return sock;
}

int main(void)
{
	int sock;
	char message[MAXMSG];
	struct sockaddr_un name;
	socklen_t size;
	int nbytes;

	unlink(SERVER);

	sock = make_named_socket(SERVER);

	while (1) {
		/* Wait for a datagram. */
		size = sizeof(name);
		nbytes = recvfrom(sock, message, MAXMSG, 0,
				  (struct sockaddr *)&name, &size);
		if (nbytes < 0) {
			perror("recfrom(server)");
			exit(EXIT_FAILURE);
		}
		/* Give a diagnostic message. */
		fprintf(stderr, "Server: got message: %s\n", message);
		message[0] = 'X';

		/* Bounce the message back to the sender. */
		nbytes = sendto(sock, message, nbytes, 0,
				(struct sockaddr *)&name, size);
		if (nbytes < 0) {
			perror("sendto(server)");
			exit(EXIT_FAILURE);
		}
	}

	return 0;
}
