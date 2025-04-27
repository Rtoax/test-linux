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

#include "tcp_helpers.h"

/**
 *  Nagle 算法为了避免网络中存在太多的小数据包，尽可能发送大的数据包。
 *  定义为在任意时刻，最多只有一个未被确认的小段。小段为小于MSS尺寸的
 *  数据块，未被确认是指数据发出去后未收到对端的ack。
 *
 *  Nagle 算法是在网速较慢的时代的产物，目前的网络环境已经不太需要该机
 *  制，该算法在linux系统中默认关闭。
 */

void tcp_nodelay(int fd)
{
	int value = 1;
	if (setsockopt(fd, SOL_TCP, TCP_NODELAY, &value, sizeof(value)) != 0)
		perror("setsockopt(TCP_NODELAY):");
}

/**
 *  libautocork
 *  git://git.kernel.org/pub/scm/linux/kernel/git/acme/libautocork
 */
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

void tcp_reuseaddr(int fd)
{
	int on = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
		perror("setsockopt(SO_REUSEADDR):");
}
