#ifndef _COMMON_H
#define _COMMON_H

#define MAX_LINE       2048
#define PORT           6023
#define BACKLOG        10
#define LISTENQ        6666
#define MAX_CONNECT    20

int tcpsocket_server(void);
int tcpsocket_client(const char *ipv6);

ssize_t readline(int fd, char *vptr, size_t maxlen);

#endif /*<_COMMON_H>*/
