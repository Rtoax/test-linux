#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <time.h>
#include <unistd.h>
#include <poll.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

void tcp_nodelay(int fd)
{
	int value = 1;
	if (setsockopt(fd, SOL_TCP, TCP_NODELAY, &value, sizeof(value)) != 0)
		perror("setsockopt(TCP_NODELAY):");
}

static void tcp_cork_value(int fd, int cork)
{
	int value = cork;
	if (setsockopt(fd, SOL_TCP, TCP_CORK, &value, sizeof(value)) != 0)
		perror("setsockopt(TCP_CORK):");
}

void tcp_cork(int fd)
{
	tcp_cork_value(fd, 1);
}

void tcp_uncork(int fd)
{
	tcp_cork_value(fd, 0);
}
