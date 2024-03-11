#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define BACKLOG 512
#define MAX_EVENTS 128

void error(char* msg);

static char *myprog;
static int max_connections;
static int portno;
static int msg_len;

void error(char* msg)
{
	perror(msg);
	printf("erreur...\n");
	exit(1);
}

static void usage(void)
{
	printf("Usage: %s -h   or\n", myprog);
	printf("       %s [-p port][-n connections][-l msglen]\n", myprog);
	printf("   -p port              set network port\n");
	printf("   -n connections       number of network connections to establish\n");
	printf("   -l msglen            message length\n");
}

int main(int argc, char *argv[])
{
	const char *opts = "p:l:n:h:";
	char c;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_len = sizeof(client_addr);
	char *buffer;
	struct epoll_event ev, events[MAX_EVENTS];
	int new_events, sock_conn_fd, epollfd;
	int sock_listen_fd;

	myprog = argv[0];
	while ((c = getopt(argc, argv, opts)) != -1) {
		switch (c) {
		case 'p':
			portno = atoi(optarg);
			break;
		case 'l':
			msg_len = atoi(optarg);
			break;
		case 'n':
			max_connections = atoi(optarg);
			break;
		case 'h':
			usage();
			exit(0);
		default:
			usage();
			exit(1);
		}
	}

	if (!portno || !msg_len) {
		usage();
		exit(1);
	}
	buffer = malloc(msg_len);
	if (!buffer) {
		fprintf(stderr, "malloc failed\n");
		exit(1);
	}

	sock_listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_listen_fd < 0) {
		error("Error creating socket..\n");
	}

	memset((char *)&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portno);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sock_listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
		error("Error binding socket..\n");

	if (listen(sock_listen_fd, BACKLOG) < 0) {
		error("Error listening..\n");
	}
	printf("message length: %d\n", msg_len);
	printf("epoll echo server listening for connections on port: %d\n", portno);


	epollfd = epoll_create(MAX_EVENTS);
	if (epollfd < 0) {
		error("Error creating epoll..\n");
	}
	ev.events = EPOLLIN;
	ev.data.fd = sock_listen_fd;

	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sock_listen_fd, &ev) == -1) {
		error("Error adding new listeding socket to epoll..\n");
	}

	while (1) {
		int i;

		new_events = epoll_wait(epollfd, events, MAX_EVENTS, -1);

		if (new_events == -1) {
			error("Error in epoll_wait..\n");
		}

		for (i = 0; i < new_events; ++i) {
			if (events[i].data.fd == sock_listen_fd) {
				sock_conn_fd = accept4(sock_listen_fd, (struct sockaddr *)&client_addr,
						       &client_len, SOCK_NONBLOCK);
				if (sock_conn_fd == -1) {
					error("Error accepting new connection..\n");
				}

				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = sock_conn_fd;
				if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sock_conn_fd, &ev) == -1) {
					error("Error adding new event to epoll..\n");
				}
			} else {
				int newsockfd = events[i].data.fd;
				int bytes_received;

				bytes_received = recv(newsockfd, buffer, msg_len, 0);
				if (bytes_received <= 0) {
					epoll_ctl(epollfd, EPOLL_CTL_DEL, newsockfd, NULL);
					shutdown(newsockfd, SHUT_RDWR);
				} else {
					send(newsockfd, buffer, bytes_received, 0);
				}
			}
		}
	}
}

