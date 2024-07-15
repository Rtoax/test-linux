#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

/* Print the contents of the home page for the server’s socket.
 * Return an indication of success. */
void get_home_page(int socket_fd)
{
	char buffer[10000];
	ssize_t nbytes;

	/* Send the HTTP GET command for the home page. */
	sprintf(buffer, "GET /\n");
	nbytes = write(socket_fd, buffer, strlen(buffer));
	if (nbytes == 0) {
		perror("write");
		return;
	}

	/* Read from the socket. The call to read may not
	 * return all the data at one time, so keep
	 * trying until we run out. */
	while (1) {
		nbytes = read(socket_fd, buffer, 10000);
		if (nbytes == 0) {
			perror("read");
			return;
		}
		/* Write the data to standard output. */
		fwrite(buffer, sizeof(char), nbytes, stdout);
	}
}

int main(int argc, char* const argv[])
{
	int socket_fd;
	struct sockaddr_in name;
	struct hostent* hostinfo;

	hostinfo = gethostbyname("www.baidu.com");
	if (hostinfo == NULL) {
		perror("gethostbyname");
		return 1;
	}

	socket_fd = socket(PF_INET, SOCK_STREAM, 0);
	name.sin_family = AF_INET;
	name.sin_addr = *((struct in_addr *)hostinfo->h_addr);
	name.sin_port = htons(80);

	/* Connect to the Web server */
	if (connect(socket_fd, &name, sizeof(struct sockaddr_in)) == -1) {
		perror("connect");
		return 1;
	}
	/* Retrieve the server’s home page. */
	get_home_page(socket_fd);
	return 0;
}
