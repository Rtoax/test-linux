#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>


#define SERVER "/tmp/serversocket"
#define CLIENT "/tmp/mysocket"
#define MAXMSG 512
#define MESSAGE "Yow!!! Are we having fun yet?!?"


int make_named_socket(const char *filename)
{
	struct sockaddr_un name;
	int sock;
	size_t size;
	/* Create the socket. */
	sock = socket(PF_LOCAL, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	/* Bind a name to the socket. */
	name.sun_family = AF_LOCAL;
	strncpy(name.sun_path, filename, sizeof(name.sun_path));
	name.sun_path[sizeof(name.sun_path) - 1] = '\0';
	size = sizeof(struct sockaddr_un);
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

	/* Make the socket. */
	sock = make_named_socket(CLIENT);

	/* Initialize the server socket address. */
	name.sun_family = AF_LOCAL;
	strcpy(name.sun_path, SERVER);
	size = strlen(name.sun_path) + sizeof(name.sun_family);

	/* Send the datagram. */
	nbytes = sendto(sock, MESSAGE, strlen(MESSAGE) + 1, 0,
			(struct sockaddr *)&name, size);
	if (nbytes < 0) {
		perror("sendto(client)");
		exit(EXIT_FAILURE);
	}

	nbytes = recvfrom(sock, message, MAXMSG, 0, NULL, 0);
	if (nbytes < 0) {
		perror("recfrom(client)");
		exit(EXIT_FAILURE);
	}
	/* Print a diagnostic message. */
	fprintf(stderr, "Client: got message: %s\n", message);

	/* Clean up. */
	remove(CLIENT);
	close(sock);
	return 0;
}
